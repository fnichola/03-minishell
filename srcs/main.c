/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/08/23 15:25:30 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

// t_minishell_data	g_data; //ここにあっても他のファイルで使えないから、minishell.hで定義する

void	init_built_in_table(void)
{
	const t_str_func_table	temp[] = {
		{"echo",	&built_in_echo},
		{"cd",		&built_in_cd},
		{"pwd",		&built_in_pwd},
		{"env",		&built_in_env},
		{"export",	&built_in_export},
		{"exit",	&built_in_exit},
	};
	t_str_func_table	*built_ins;

	built_ins = malloc_error_check(sizeof(temp));
	g_data.num_built_ins = sizeof(temp) / sizeof(t_str_func_table);
	printf("num_built_ins = %d\n", g_data.num_built_ins);
	ft_memcpy(built_ins, temp, sizeof(temp));
	g_data.built_ins = built_ins;
}

size_t	argv_len(char **argv)
{
	size_t	i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}

void	free_command_table(void *ptr)
{
	size_t		i;
	t_command	*command;

	command = (t_command *)ptr;
	i = 0;
	while (command->argv && command->argv[i])
	{
		free(command->argv[i]);
		i++;
	}
	free(command->argv);
	free(command);
}

void	built_in_exit(char **argv)
{
	int	ret;
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;

	ft_lstclear(&g_data.command_table, free_command_table);
	if (argc == 1)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else if (argc == 2)
	{
		printf("exit\n");
		ret = ft_atoi(argv[1]);
		exit(ret);
	}
	else
	{
		printf("too many arguments\n"); //need a separate error function
	}
}

void	close_exec_fds(void)
{
	size_t	i;

	i = 0;
	while (g_data.exec_fds[i])
	{
		if ((g_data.exec_fds[i])[0] > STDOUT_FILENO)
			close((g_data.exec_fds[i])[0]);
		if ((g_data.exec_fds[i])[1] > STDOUT_FILENO)
			close((g_data.exec_fds[i])[1]);
		i++;
	}
}

void	search_path_and_exec(char **argv, char **envp)
{
	char	**paths;
	char	*pathname;
	char	*temp;
	size_t	i;

	printf("search\n");
	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		pathname = ft_strjoin(temp, argv[0]);
		free(temp);
		execve(pathname, argv, envp);
		free(pathname);
		free(paths[i]);
		paths[i] = NULL;
		i++;
	}
	free(paths);
	exit_error("Can't find command.");
}

char	*str_tolower(char *str)
{
	char	*str_lower;
	size_t	i;

	str_lower = ft_strdup(str);
	i = 0;
	while (str_lower[i])
	{
		str_lower[i] = ft_tolower(str_lower[i]);
		i++;
	}
	return (str_lower);
}

bool	lookup_and_exec_built_in(char **argv)
{
	bool	is_builtin;
	size_t	i;
	char	*str;

	str = str_tolower(argv[0]);
	is_builtin = false;
	i = 0;
	while (i < g_data.num_built_ins)
	{
		if (is_str_match(str, g_data.built_ins[i].name))
		{
			g_data.built_ins[i].func(argv);
			is_builtin = true;
			break ;
		}
		i++;
	}
	free(str);
	return (is_builtin);
}

bool	execute_built_in(char **argv)
{
	bool	is_builtin;
	int		old_fd[2];

	old_fd[0] = dup(STDIN_FILENO);
	old_fd[1] = dup(STDOUT_FILENO);
	dup2((g_data.exec_fds[g_data.cmd_index])[0], STDIN_FILENO);
	dup2((g_data.exec_fds[g_data.cmd_index])[1], STDOUT_FILENO);
	is_builtin = lookup_and_exec_built_in(argv);
	dup2(old_fd[0], STDIN_FILENO);
	close(old_fd[0]);
	dup2(old_fd[1], STDOUT_FILENO);
	close(old_fd[1]);
	return (is_builtin);
}

void	execute_external(char **argv, char **envp)
{
	pid_t	pid;
	int		status;
	size_t	i;

	pid = fork();
	if (pid == 0)// 子プロセス
	{
		dup2((g_data.exec_fds[g_data.cmd_index])[0], STDIN_FILENO);
		dup2((g_data.exec_fds[g_data.cmd_index])[1], STDOUT_FILENO);
		close_exec_fds();
		if (ft_strchr(argv[0], '/'))
			execve(argv[0], argv, envp);
		else
			search_path_and_exec(argv, envp);
	}
	else
	{
		if (g_data.cmd_index == g_data.num_cmds - 1)
		{

			printf("close fds after executing last command\n");
			close_exec_fds();
			waitpid(pid, &status, WUNTRACED);
		}
	}
}

void	execute_simple_command(char **argv, char **envp)
{
	if (execute_built_in(argv))
		return ;
	else
		execute_external(argv, envp);
}


void	connect_pipes()
{
	int		pipe_fd[2];
	size_t	i;

	g_data.exec_fds = malloc_error_check(sizeof(int *) * (g_data.num_cmds + 1));
	i = 0;
	while (i < g_data.num_cmds)
	{
		g_data.exec_fds[i] = malloc_error_check(sizeof(int) * 2);
		i++;
	}
	g_data.exec_fds[i] = NULL;
	if (g_data.num_cmds == 1)
	{
		(g_data.exec_fds[0])[0] = STDIN_FILENO;
		(g_data.exec_fds[0])[1] = STDOUT_FILENO;
	}
	else
	{
		(g_data.exec_fds[0])[0] = STDIN_FILENO;
		i = 1;
		while (i < g_data.num_cmds)
		{
			ft_wpipe(pipe_fd);
			printf("pipe_fd = %d, %d\n", pipe_fd[0], pipe_fd[1]);
			(g_data.exec_fds[i - 1])[1] = pipe_fd[1];
			(g_data.exec_fds[i])[0] = pipe_fd[0];
			i++;
		}
		i--;
		(g_data.exec_fds[i])[1] = STDOUT_FILENO;
	}
	i = 0;
	while (i < g_data.num_cmds)
	{
		printf("exec_fds[%zu] = %d, %d\n", i, (g_data.exec_fds[i])[0], (g_data.exec_fds[i])[1]);
		i++;
	}
}

int	execute_commands(char **envp)
{
	t_command	*command;
	t_list		*command_table_ptr;
	char		**argv;
	int			i;
	int			**exec_fds;

	i = -1;
	command_table_ptr = g_data.command_table;//ここでグローバル変数から、コマンドを代入している
	g_data.num_cmds = ft_lstsize(g_data.command_table);
	connect_pipes();

	g_data.cmd_index = 0;
	while (g_data.cmd_index < g_data.num_cmds)//num_cmdsはパイプがあれば、増えていく
	{
		// printf("num_cmds = %d\n", num_cmds);
		command = (t_command *)command_table_ptr->content;
		argv = command->argv;//ここでargvにcommandのargvが代入されているので、built_inにはargvを渡せばいい。
		if (!argv || !argv[0])
			return (0);
		execute_simple_command(argv, envp);
		command_table_ptr = command_table_ptr->next;
		g_data.cmd_index++;
	}
	i = 0;
	while(g_data.exec_fds[i])
	{
		free(g_data.exec_fds[i]);
		i++;
	}
	free(g_data.exec_fds);
	g_data.exec_fds = NULL;
	return (0);
}

int	minishell(char **envp)
{
	int			status;
	char		*line;
	t_list		*tokens;

	g_data.env_list = init_env_list(envp);
	g_data.command_table = NULL;
	init_built_in_table();
	status = 0;
	printf("minishell\n");
	while (!status)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		tokens = tokenizer(line);
		// printf("tokens %s\n", (char *)tokens->next->content);
		g_data.command_table = parser(tokens, g_data.env_list);
		// printf("g_data.command_table %s\n", (char *)g_data.command_table->content->);
		free(line);
		printf("before execute\n");
			status = execute_commands(envp);
		ft_lstclear(&g_data.command_table, free_command_table);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc == 1)
	{
		minishell(envp);
	}
	else
	{
		ft_printf("error\n");
	}
	return (0);
}
