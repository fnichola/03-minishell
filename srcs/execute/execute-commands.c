/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 09:22:05 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/14 02:54:56 by fnichola         ###   ########.fr       */
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

bool	execute_built_in(t_command *cmd)
{
	bool	is_builtin;
	int		old_fd[2];

	old_fd[0] = dup(STDIN_FILENO);
	old_fd[1] = dup(STDOUT_FILENO);
	dup2(cmd->input_fd, STDIN_FILENO);//redirectはここの第一引数がopenしたfdである必要
	dup2(cmd->output_fd, STDOUT_FILENO);
	is_builtin = lookup_and_exec_built_in(cmd->argv);
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

int		execute_external(t_command *cmd, char **envp)
{
	pid_t	pid;
	// int		status;

	pid = fork();
	if (pid == 0)// 子プロセス
	{
		dup2(cmd->input_fd, STDIN_FILENO);
		dup2(cmd->output_fd, STDOUT_FILENO);
		close_exec_fds();
		if (ft_strchr(cmd->argv[0], '/'))
			execve(cmd->argv[0], cmd->argv, envp);
		else
			search_path_and_exec(cmd->argv, envp);
	}
	return (pid);
}

static void	execute_simple_command(t_command *cmd)
{
	char	**envp;

	debug_log("execute_simple_command: ");
	for (int i=0; cmd->argv[i]; i++)
		debug_log("%s ", cmd->argv[i]);
	debug_log("\n");

	if (execute_built_in(cmd))
		return ;
	else
	{
		envp = export_to_envp();
		cmd->pid = execute_external(cmd, envp);
		free_envp(envp);
	}
}

static void	execute_commands_loop(void)
{
	t_command	*ct;
	int			status;

	ct = g_data.command_table;
	while (ct)//num_cmdsはパイプがあれば、増えていく
	{
		if (!ct->argv || !ct->argv[0])
			return ;
		execute_simple_command(ct);
		ct = ct->next;
	}
	close_exec_fds();
	ct = g_data.command_table;
	while (ct)
	{
		if (ct->pid)
			waitpid(ct->pid, &status, WUNTRACED);
		ct = ct->next;
	}
}

int	execute_commands(void)
{
	prepare_exec_fds();
	execute_commands_loop();
	close_exec_fds();
	free_command_table();
	return (0);
}
