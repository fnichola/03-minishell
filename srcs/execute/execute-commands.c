/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 09:22:05 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/26 17:50:19 by atomizaw         ###   ########.fr       */
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
			debug_log("is_str_match\n");
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

	debug_log("command not found- argv[0] %s\n", argv[0]);
	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		pathname = ft_strjoin(temp, argv[0]);
		free(temp);
		if (execve(pathname, argv, envp) != -1)
			free(pathname);
		free(paths[i]);
		paths[i] = NULL;
		i++;
	}
	free(paths);
	ft_puterror(argv[0], " command not found", NULL);
	exit(127);
}
// void	check_execve(char **argv)
// {
	 
// }

int		execute_external(t_command *cmd, char **envp)
{
	pid_t	pid;
	// int		status;

	pid = fork();
	if (pid == 0)// 子プロセス
	{
		ft_wsignal(SIGINT, signal_handler_child);
		ft_wsignal(SIGQUIT, SIG_DFL);
		dup2(cmd->input_fd, STDIN_FILENO);
		dup2(cmd->output_fd, STDOUT_FILENO);
		close_exec_fds();
		if (ft_strchr(cmd->argv[0], '/'))
		{
			debug_log("command not found 絶対パス %s\n", cmd->argv[0]);
			// check_execve(cmd->argv[0], envp);
			if (execve(cmd->argv[0], cmd->argv, envp) == -1)
			{
				ft_puterror(cmd->argv[0], "No such file or directory", NULL);
				exit(127);
			}
		}
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
	ft_wsignal(SIGINT, SIG_IGN);
	if (execute_built_in(cmd))
	{
		g_data.built_in_count++;
		return ;
	}
	else
	{
		envp = export_to_envp();
		cmd->pid = execute_external(cmd, envp);
		free_envp(envp);
	}
	// ft_wsignal(SIGINT, signal_handler); //意味ない？
}

static void	execute_commands_loop(int *e_status)
{
	t_command	*ct;

	ct = g_data.command_table;
	while (ct)//num_cmdsはパイプがあれば、増えていく
	{
		if (!ct->argv || !ct->argv[0])
			return ;
		execute_simple_command(ct);
		g_data.is_piped++;
		ct = ct->next;
	}
	close_exec_fds();
	ct = g_data.command_table;
	while (ct)
	{
		if (ct->pid)
		{
			debug_log("waitpid\n");
			waitpid(ct->pid, e_status, WUNTRACED);
			ft_wsignal(SIGINT, signal_handler);
		}
		debug_log("execute_command_loop %d\n", *e_status);
		ct = ct->next;
	}
	g_data.exit_status = 0;
	ft_wsignal(SIGINT, signal_handler); //ここじゃないと特定のパターンでシグナルを受け付けなくなる
}

int	execute_commands(void)
{
	int		e_status;

	g_data.built_in_count = 0;
	prepare_exec_fds();
	execute_commands_loop(&e_status);
	debug_log("g_data.is_piped %d\n", g_data.is_piped);
	debug_log("g_data.built_in_count %d\n", g_data.built_in_count);
	if (g_data.is_piped == 1 || g_data.built_in_count == 0)//パイプとかの時だけ入るようにする exit 4 | lsはexit_status = 0でいい
		set_status_from_child_status(e_status);
	close_exec_fds();
	free_command_table();
	debug_log("execute_commands argv[1]  g_data.exit_status %d\n", g_data.exit_status);
	return (0);
}
