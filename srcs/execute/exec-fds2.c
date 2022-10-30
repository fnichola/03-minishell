/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec-fds2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:00:54 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 15:01:40 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_exec_fds(void)
{
	t_command	*ct;

	ct = g_data.command_table;
	while (ct)
	{
		if (ct->input_fd != STDIN_FILENO)
			close(ct->input_fd);
		if (ct->output_fd != STDOUT_FILENO)
			close(ct->output_fd);
		ct = ct->next;
	}
}

static int	update_input_redirect(t_redirect *r, t_command *cmd)
{
	int	fd;

	if (r->append)
		fd = heredoc(r, cmd);
	else
	{
		fd = open(r->filename, O_RDONLY);
		if (fd >= 0)
		{
			if (cmd->input_fd != STDIN_FILENO)
				close(cmd->input_fd);
			cmd->input_fd = fd;
		}
	}
	return (fd);
}

static int	update_output_redirect(t_redirect *r, t_command *cmd)
{
	int	fd;

	fd = open(r->filename, O_WRONLY | O_CREAT | !r->append * O_TRUNC | \
		r->append * O_APPEND, 0666);
	if (fd >= 0)
	{
		if (cmd->output_fd != STDOUT_FILENO)
			close(cmd->output_fd);
		cmd->output_fd = fd;
	}
	return (fd);
}

int	process_redirect_list(t_command *cmd)
{
	t_redirect	*r;
	int			fd;

	r = cmd->redirects;
	fd = 0;
	while (r)
	{
		if (r->type == INPUT_REDIRECT)
			fd = update_input_redirect(r, cmd);
		else if (r->type == OUTPUT_REDIRECT)
			fd = update_output_redirect(r, cmd);
		if (fd < 0)
		{
			ft_perror(r->filename);
			break ;
		}
		r = r->next;
	}
	return (fd);
}
