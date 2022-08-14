/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/08/14 21:50:48 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include "struct.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

// t_minishell_data	g_data; //ここにあっても他のファイルで使えないから、minishell.hで定義する

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

void	builtin_exit(int argc, char **argv)
{
	int	ret;

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
		printf("too many arguments\n");	//need a separate error function
	}
}

// void free_token_list (void *ptr)
// {
// 	t_token	*token;

// 	token = (t_token *)ptr;
// 	free(token->word);
// 	free(token);

// }

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
		i++;
	}
	free(paths);
	exit_error("Can't find command.");
}

pid_t	execute_simple_command(char **argv, char **envp, int **exec_fds, t_envlist *e_list, int i)
{
	pid_t	pid;
	// int		i;

	// i = 0;
	if (!ft_strncmp(argv[0], "exit", \
	ft_strlen(argv[0])) && ft_strlen(argv[0]) >= 4)
	{
		builtin_exit(argv_len(argv), argv);
	}
	pid = fork();
	if (pid == 0)// 子プロセス
	{
		if (i != 0)
		{
			dup2(exec_fds[i - 1][0], STDIN_FILENO);
		}
		if (i == 0)
		{
			dup2(exec_fds[i][1], 1);//この後の処理が不明。ここでpipeに出力を書き込まれる
			close(exec_fds[i][1]);
		}
		printf("子プロセス\n");
		// close(exec_fds.in_fd);
		// close(exec_fds.out_fd);
		// close(exec_fds.pipe_fd[0]);
		// close(exec_fds.pipe_fd[1]);
		if (!ft_strncmp(argv[0], "echo", ft_strlen(argv[0])))
		{
			built_in_echo(argv, e_list);
		}
		else if (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])))
		{
			built_in_cd(argv, e_list);
		}
		else if (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])))
		{
			built_in_pwd();
		}
		else if (!ft_strncmp(argv[0], "env", ft_strlen(argv[0])))
		{
			built_in_env(e_list);
		}
		else if (!ft_strncmp(argv[0], "export", ft_strlen(argv[0])))
		{
			built_in_export(argv, e_list);
		}
		else if (ft_strchr(argv[0], '/'))
			execve(argv[0], argv, envp);
		else
			search_path_and_exec(argv, envp);
	}
	else
	{
		close(exec_fds[i][0]);
		printf("親プロセス\n");
	}
	return (pid);
}

void	execute_last_command(char **argv, char **envp, int **exec_fds, t_envlist *e_list, int i)
{
	int		status;
	pid_t	pid;

	printf("last\n");
	if (!ft_strncmp(argv[0], "exit", \
	ft_strlen(argv[0])) && ft_strlen(argv[0]) >= 4)
	{
		builtin_exit(argv_len(argv), argv);
	}
	pid = fork();
	if (pid == 0)// 子プロセス
	{
		if (argv[1])
		{
			if (i != 0)
			{
				dup2(exec_fds[i - 1][0], STDIN_FILENO);
				close(exec_fds[i - 1][1]);
			}
			else
			{
				dup2(exec_fds[i][1], 1); //この後の処理が不明。ここでpipeに出力を書き込まれる
				close(exec_fds[i][1]);
			}
			// close(exec_fds[i][1]);
		}
		printf("子プロセス\n");
		if (!ft_strncmp(argv[0], "echo", ft_strlen(argv[0])))
			built_in_echo(argv, e_list);
		else if (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])))
			built_in_cd(argv, e_list);
		else if (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])))
			built_in_pwd();
		else if (!ft_strncmp(argv[0], "env", ft_strlen(argv[0])))
			built_in_env(e_list);
		else if (!ft_strncmp(argv[0], "export", ft_strlen(argv[0])))
			built_in_export(argv, e_list);
		else if (ft_strchr(argv[0], '/'))
			execve(argv[0], argv, envp);
		else
			search_path_and_exec(argv, envp);
	}
	else
	{
		close(exec_fds[i][1]);
		printf("親プロセス\n");
	}
	waitpid(pid, &status, WUNTRACED);
}

void	execute_piped_command(char **argv, char **envp, int **exec_fds, t_envlist *e_list, int i)
{
	printf("piped\n");
	printf("exec_fds[0] %d\n", exec_fds[i][0]);
	pid_t	pid;

	if (!ft_strncmp(argv[0], "exit", \
	ft_strlen(argv[0])) && ft_strlen(argv[0]) >= 4)
	{
		builtin_exit(argv_len(argv), argv);
	}
	pid = fork();
	if (pid == 0)// 子プロセス
	{
		if (i != 0)
		{
			dup2(exec_fds[i][1], 1);
			dup2(exec_fds[i - 1][0], STDIN_FILENO);
			close(exec_fds[i - 1][1]);
		}
		if (i == 0)
		{
			dup2(exec_fds[i][1], 1);//この後の処理が不明。ここでpipeに出力を書き込まれる
			close(exec_fds[i][1]);
		}
		printf("子プロセス\n");
		if (!ft_strncmp(argv[0], "echo", ft_strlen(argv[0])))
		{
			built_in_echo(argv, e_list);
		}
		else if (!ft_strncmp(argv[0], "cd", ft_strlen(argv[0])))
		{
			built_in_cd(argv, e_list);
		}
		else if (!ft_strncmp(argv[0], "pwd", ft_strlen(argv[0])))
		{
			built_in_pwd();
		}
		else if (!ft_strncmp(argv[0], "env", ft_strlen(argv[0])))
		{
			built_in_env(e_list);
		}
		else if (!ft_strncmp(argv[0], "export", ft_strlen(argv[0])))
		{
			built_in_export(argv, e_list);
		}
		else if (ft_strchr(argv[0], '/'))
			execve(argv[0], argv, envp);
		else
			search_path_and_exec(argv, envp);
		close(exec_fds[i][1]);
		close(exec_fds[i][0]);
	}
	else
	{
		close(exec_fds[i][1]);
		printf("親プロセス\n");
	}
}

int	execute_commands(char **envp, t_envlist *e_list)
{
	t_command	*command;
	t_list		*command_table_ptr;
	char		**argv;
	int			number_of_simple_commands;
	int			i;
	int			**exec_fds;

	i = -1;
	command_table_ptr = g_data.command_table;//ここでグローバル変数から、コマンドを代入している
	number_of_simple_commands = ft_lstsize(g_data.command_table);
	exec_fds = (int **)malloc_error_check(sizeof(int *) * number_of_simple_commands);
	while (++i < number_of_simple_commands)
		exec_fds[i] = (int *)malloc_error_check(sizeof(int) * 2);
	i = -1;
	while (++i < number_of_simple_commands)
		ft_wpipe(exec_fds[i]);
	i = 0;
	while (i < number_of_simple_commands)//number_of_simple_commandsはパイプがあれば、増えていく
	{
		printf("start\n");
		printf("number_of_simple_commands = %d\n", number_of_simple_commands);
		command = (t_command *)command_table_ptr->content;
		argv = command->argv;//ここでargvにcommandのargvが代入されているので、built_inにはargvを渡せばいい。
		if (!argv || !argv[0])
			return (0);
		if (i == number_of_simple_commands - 1) // last simple command
			execute_last_command(argv, envp, exec_fds, e_list, i);
		else
			execute_piped_command(argv, envp, exec_fds, e_list, i);
		command_table_ptr = command_table_ptr->next;
		i++;
	}
	return (0);
}

int	minishell(char **envp)
{
	int			status;
	char		*line;
	t_envlist	*env_list;
	t_list		*tokens;

	env_list = init_env_list(envp);
	g_data.command_table = NULL;
	status = 0;
	printf("minishell\n");
	while (!status)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		tokens = tokenizer(line);
		// printf("tokens %s\n", (char *)tokens->next->content);
		g_data.command_table = parser(tokens);
		// printf("g_data.command_table %s\n", (char *)g_data.command_table->content->);
		free(line);
		status = execute_commands(envp, env_list);
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
