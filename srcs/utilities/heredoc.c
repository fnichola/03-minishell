/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:37:23 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 14:40:19 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_read(t_redirect *r, t_command *cmd)
{
	char	*line;

	while (!g_data.sig_int)
	{
		line = readline("> ");
		if (!line)
			break ;
		else if (g_data.sig_int || is_str_match(line, r->filename))
		{
			free(line);
			break ;
		}
		heredoc_expand_variables(&line);
		heredoc_add_line(cmd, line);
	}
}

int	heredoc(t_redirect *r, t_command *cmd)
{
	int		pipe_fd[2];
	int		i;

	pipe(pipe_fd);
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	cmd->input_fd = pipe_fd[0];
	g_data.sig_int = false;
	heredoc_read(r, cmd);
	i = 0;
	while (!g_data.sig_int && cmd->heredoc && cmd->heredoc[i])
	{
		write(pipe_fd[1], cmd->heredoc[i], ft_strlen(cmd->heredoc[i]));
		write(pipe_fd[1], "\n", 1);
		i++;
	}
	close(pipe_fd[1]);
	return (cmd->input_fd);
}
