/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec-fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:58:36 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 16:45:40 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	connect_redirects(void)
{
	t_command	*ct;

	ct = g_data.command_table;
	while (ct)
	{
		if (process_redirect_list(ct) < 0)
			ct = del_command(ct);
		else
			ct = ct->next;
	}
}

static void	connect_pipes(void)
{
	int			pipe_fd[2];
	t_command	*ct;

	ct = g_data.command_table;
	ct->input_fd = STDIN_FILENO;
	while (ct->next)
	{
		ft_wpipe(pipe_fd);
		ct->output_fd = pipe_fd[1];
		ct->next->input_fd = pipe_fd[0];
		ct = ct->next;
	}
	ct->output_fd = STDOUT_FILENO;
}

void	prepare_exec_fds(void)
{
	connect_pipes();
	connect_redirects();
}
