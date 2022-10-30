/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 09:22:05 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 14:28:44 by atomizaw         ###   ########.fr       */
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

	paths = ft_split(ft_getenv("PATH"), ':');
	i = 0;
	while (paths && paths[i])
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
	ft_puterror(argv[0], "command not found", NULL);
	exit(127);

}

void	check_execve(char *argv)
{
	// if (stat(argv[0], ))
	// {

	// 	printf("open失敗");
	// 	ft_perror(NULL);
	// 	exit(126);
	// }
	if (access(argv, F_OK) == -1)
	{
		ft_perror(NULL);
		exit(127);
	}
	else if (access(argv, X_OK))
	{
		ft_perror(NULL);
		exit(127);
	}
}

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
			check_execve(cmd->argv[0]);
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
	size_t i = 0;
	if (cmd->heredoc)
	{
		while(cmd->heredoc[i])
		{
			write(cmd->input_fd, cmd->heredoc[i], ft_strlen(cmd->heredoc[i]));
			write(cmd->input_fd, "\n", 1);
			i++;
		}
		close(cmd->input_fd);
	}
}

static void	execute_commands_loop(void)
{
	t_command	*ct;
	int	wstatus;

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
		{
			waitpid(ct->pid, &wstatus, WUNTRACED);
			set_status_from_child_status(wstatus);
		}
		ct = ct->next;
	}
	ft_wsignal(SIGINT, signal_handler); //ここじゃないと特定のパターンでシグナルを受け付けなくなる
}

int	execute_commands(void)
{
	g_data.built_in_count = 0;
	if (!g_data.command_table)
		return (0);
	prepare_exec_fds();
	execute_commands_loop();
	close_exec_fds();
	free_command_table();
	return (0);
}
