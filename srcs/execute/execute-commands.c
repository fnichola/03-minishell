/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 09:22:05 by fnichola          #+#    #+#             */
/*   Updated: 2022/09/26 00:34:05 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	else // 親プロセス
	{
		if (g_data.cmd_index == g_data.num_cmds - 1)
		{
			close_exec_fds();
			waitpid(pid, &status, WUNTRACED);
		}
	}
}

static void	execute_simple_command(char **argv)
{
	char	**envp;

	if (execute_built_in(argv))
		return ;
	else
	{
		envp = export_to_envp();
		execute_external(argv, envp);
		free_envp(envp);
	}
}

static void	execute_commands_loop(t_list *command_table_ptr, char **envp)
{
	t_command	*command;
	char		**argv;

	g_data.cmd_index = 0;
	while (g_data.cmd_index < g_data.num_cmds)//num_cmdsはパイプがあれば、増えていく
	{
		// printf("num_cmds = %d\n", num_cmds);
		command = (t_command *)command_table_ptr->content;
		argv = command->argv;//ここでargvにcommandのargvが代入されているので、built_inにはargvを渡せばいい。
		if (!argv || !argv[0])
			return ;
		execute_simple_command(argv);
		command_table_ptr = command_table_ptr->next;
		g_data.cmd_index++;
	}
}

int	execute_commands(char **envp)
{
	t_command	*command;
	char		**argv;
	int			**exec_fds;

	g_data.num_cmds = ft_lstsize(g_data.command_table);
	init_exec_fds();
	execute_commands_loop(g_data.command_table, envp);
	free_exec_fds();
	return (0);
}
