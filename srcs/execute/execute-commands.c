/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 09:22:05 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 16:43:51 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_simple_command(t_command *cmd)
{
	char	**envp;
	size_t	i;

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
	i = 0;
	if (cmd->heredoc)
	{
		while (cmd->heredoc[i])
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
	int			wstatus;

	ct = g_data.command_table;
	while (ct)
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
	ft_wsignal(SIGINT, signal_handler);
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
