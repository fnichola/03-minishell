/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:54:09 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 13:54:47 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	execute_external(t_command *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
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
