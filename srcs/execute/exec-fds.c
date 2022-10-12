/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec-fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:58:36 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/12 07:57:41 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	alloc_exec_fds(void)
{
	size_t	i;

	g_data.exec_fds = malloc_error_check(sizeof(int *) * (g_data.num_cmds + 1));
	i = 0;
	while (i < g_data.num_cmds)
	{
			g_data.exec_fds[i] = malloc_error_check(sizeof(int) * 2);
		i++;
	}
	g_data.exec_fds[i] = NULL;
}

void	free_exec_fds(void)
{
	size_t	i;

	i = 0;
	while (g_data.exec_fds[i])
	{
		free(g_data.exec_fds[i]);
		i++;
	}
	free(g_data.exec_fds);
	g_data.exec_fds = NULL;
}

void	close_exec_fds(void)
{
	size_t	i;

	i = 0;
	while (g_data.exec_fds[i])
	{
		if ((g_data.exec_fds[i])[0] > STDOUT_FILENO)
			close((g_data.exec_fds[i])[0]);
		if ((g_data.exec_fds[i])[1] > STDOUT_FILENO)
			close((g_data.exec_fds[i])[1]);
		i++;
	}
}

static void	create_redirects(void)
{
	t_list		*cmd_table_ptr;
	t_command	*cmd;
	size_t		i;

	cmd_table_ptr = g_data.command_table;
	i = 0;
	while (cmd_table_ptr)
	{
		cmd = (t_command *)cmd_table_ptr->content;
		if (cmd->input_redirect)
		{
			if ((g_data.exec_fds[i])[0] != STDIN_FILENO)
				close((g_data.exec_fds[i])[0]);
			(g_data.exec_fds[i])[0] = open(cmd->input_redirect->filename, O_RDONLY);
			debug_log("create_redirects: opened %s at fd=%d\n", cmd->input_redirect->filename, (g_data.exec_fds[i])[0]);
		}
		if (cmd->output_redirect)
		{
			if ((g_data.exec_fds[i])[1] != STDOUT_FILENO)
				close((g_data.exec_fds[i])[1]);
			(g_data.exec_fds[i])[1] = open(cmd->output_redirect->filename, O_WRONLY | O_CREAT | !cmd->output_redirect->append * O_TRUNC | cmd->output_redirect->append * O_APPEND, 0666);
			debug_log("create_redirects: opened %s at fd=%d\n", cmd->output_redirect->filename, (g_data.exec_fds[i])[1]);
		}
		cmd_table_ptr = cmd_table_ptr->next;
		i++;
	}
}

static void	create_pipes(void)
{
	size_t		i;
	int			pipe_fd[2];

	(g_data.exec_fds[0])[0] = STDIN_FILENO;
	i = 1;
	while (i < g_data.num_cmds)
	{
		ft_wpipe(pipe_fd);
		(g_data.exec_fds[i - 1])[1] = pipe_fd[1];
		(g_data.exec_fds[i])[0] = pipe_fd[0];
		i++;
	}
	i--;
	(g_data.exec_fds[i])[1] = STDOUT_FILENO;
}

void	init_exec_fds(void)
{
	alloc_exec_fds();
	create_pipes();
	create_redirects();
}
