/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec-fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:58:36 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/25 13:24:15 by fnichola         ###   ########.fr       */
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

void	heredoc_add_line(t_command *cmd, char *line)
{
	static size_t	size = 8;
	size_t			i;
	size_t			j;
	char			**new_heredoc;

	if (!cmd->heredoc)
	{
		cmd->heredoc = malloc_error_check(sizeof(char *) * size);
		cmd->heredoc[0] = NULL;
	}
	i = 0;
	while (cmd->heredoc[i])
		i++;
	if (i >= size - 1)
	{
		size *= 2;
		new_heredoc = malloc_error_check(sizeof(char *) * size);
		j = 0;
		while (j < i)
		{
			new_heredoc[j] = cmd->heredoc[j];
			j++;
		}
		free (cmd->heredoc);
		cmd->heredoc = new_heredoc;
	}
	cmd->heredoc[i] = line;
	cmd->heredoc[i + 1] = NULL;
}

static int	update_input_redirect(t_redirect *r, t_command *cmd)
{
	int		fd;
	char	*line;
	int		pipe_fd[2];
	int		i;

	if (r->append)
	{
		pipe(pipe_fd);
		if (cmd->input_fd != STDIN_FILENO)
			close(cmd->input_fd);
		cmd->input_fd = pipe_fd[0];
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			else if (is_str_match(line, r->filename))
			{
				free(line);
				break ;
			}
			heredoc_add_line(cmd, line);
		}
		debug_log("update_input_redirect: heredoc end\n");

		i = 0;
		while(cmd->heredoc[i])
		{
			write(pipe_fd[1], cmd->heredoc[i], ft_strlen(cmd->heredoc[i]));
			write(pipe_fd[1], "\n", 1);
			i++;
		}
		close(pipe_fd[1]);
		return (cmd->input_fd);
	}
	else
	{
		fd = open(r->filename, O_RDONLY);
		if (fd >= 0)
		{
			if (cmd->input_fd != STDIN_FILENO)
				close(cmd->input_fd);
			cmd->input_fd = fd;
			debug_log("connect_redirects: opened %s at fd=%d\n", r->filename, fd);
		}
		return (fd);
	}
}

static int	update_output_redirect(t_redirect *r, t_command *cmd)
{
	int	fd;

	fd = open(r->filename, O_WRONLY | O_CREAT | !r->append * O_TRUNC | r->append * O_APPEND, 0666);
	if (fd >= 0)
	{
		if (cmd->output_fd != STDOUT_FILENO)
			close(cmd->output_fd);
		cmd->output_fd = fd;
		debug_log("connect_redirects: opened %s at fd=%d\n", r->filename, fd);
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
	debug_log("init_exec_fds: \n");
	int i = 0;
	for (t_command *ct = g_data.command_table; ct; ct = ct->next)
	{
		debug_log("\t%d: %d, %d\n", i, ct->input_fd, ct->output_fd);
		i++;
	}
}
