/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec-fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:58:36 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/12 09:00:06 by fnichola         ###   ########.fr       */
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

/**
 * Delete a single command from the command_table
 */
t_list *del_command(t_list *item)
{
	t_list	*cmd_table;
	t_list	*previous_item;
	t_list	*new_ptr;

	if (!item)
		return (NULL);
	cmd_table = g_data.command_table;
	previous_item = NULL;
	while (cmd_table && cmd_table != item)
	{
		previous_item = cmd_table;
		cmd_table = cmd_table->next;
	}
	if (cmd_table != item)
		return (NULL);
	debug_log("del_command: deleting simple command argv[0]=%s\n", ((t_command *)item->content)->argv[0]);
	free_command_table(item->content);
	new_ptr = item->next;
	if (previous_item)
		previous_item->next = new_ptr;
	else
		g_data.command_table = new_ptr;
	free(item);
	if (!new_ptr)
		g_data.num_cmds = 0;
	else
		g_data.num_cmds--;
	return (new_ptr);
}

static void	create_redirects(void)
{
	t_list		*cmd_table_ptr;
	t_command	*cmd;
	size_t		i;
	int			fd;

	cmd_table_ptr = g_data.command_table;
	i = 0;
	while (cmd_table_ptr)
	{
		cmd = (t_command *)cmd_table_ptr->content;
		if (cmd->input_redirect)
		{
			if ((g_data.exec_fds[i])[0] != STDIN_FILENO)
				close((g_data.exec_fds[i])[0]);
			fd = open(cmd->input_redirect->filename, O_RDONLY);
			if (fd >= 0)
			{
				debug_log("create_redirects: opened %s at fd=%d\n", cmd->input_redirect->filename, fd);
				(g_data.exec_fds[i])[0] = fd;
			}
			else
			{
				ft_perror(cmd->input_redirect->filename);
				cmd_table_ptr = del_command(cmd_table_ptr);
				continue ;
			}
		}
		if (cmd->output_redirect)
		{
			if ((g_data.exec_fds[i])[1] != STDOUT_FILENO)
				close((g_data.exec_fds[i])[1]);
			fd = open(cmd->output_redirect->filename, O_WRONLY | O_CREAT | !cmd->output_redirect->append * O_TRUNC | cmd->output_redirect->append * O_APPEND, 0666);
			if (fd >= 0)
			{
				debug_log("create_redirects: opened %s at fd=%d\n", cmd->output_redirect->filename, fd);
				(g_data.exec_fds[i])[1] = fd;
			}
			else
			{
				ft_perror(cmd->output_redirect->filename);
				cmd_table_ptr = del_command(cmd_table_ptr);
				continue ;
			}
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
	debug_log("init_exec_fds: \n");
	for (int i=0; g_data.exec_fds[i]; ++i)
		debug_log("\texec_fds[%d] = (%d, %d)\n", i, (g_data.exec_fds[i])[0], (g_data.exec_fds[i])[1]);
}
