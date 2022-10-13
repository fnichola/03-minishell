/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec-fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:58:36 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 09:19:07 by fnichola         ###   ########.fr       */
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

static int	add_input_redirect(t_redirect *r, size_t i)
{
	int	fd;

	fd = open(r->filename, O_RDONLY);
	if (fd >= 0)
	{
		if ((g_data.exec_fds[i])[0] != STDIN_FILENO)
			close((g_data.exec_fds[i])[0]);
		debug_log("create_redirects: opened %s at fd=%d\n", r->filename, fd);
		(g_data.exec_fds[i])[0] = fd;
	}
	return (fd);
}

static int	add_output_redirect(t_redirect *r, size_t i)
{
	int	fd;

	fd = open(r->filename, O_WRONLY | O_CREAT | !r->append * O_TRUNC | r->append * O_APPEND, 0666);
	if (fd >= 0)
	{
		if ((g_data.exec_fds[i])[1] != STDOUT_FILENO)
			close((g_data.exec_fds[i])[1]);
		debug_log("create_redirects: opened %s at fd=%d\n", r->filename, fd);
		(g_data.exec_fds[i])[1] = fd;
	}
	return (fd);
}

static void	create_redirects(void)
{
	t_list		*cmd_table_ptr;
	t_command	*cmd;
	size_t		i;
	int			fd;
	t_redirect	*r;
	bool		redirect_error;

	cmd_table_ptr = g_data.command_table;
	i = 0;
	while (cmd_table_ptr)
	{
		redirect_error = false;
		cmd = (t_command *)cmd_table_ptr->content;
		r = cmd->redirects;
		while (r)
		{
			if (r->type == INPUT_REDIRECT)
				fd = add_input_redirect(r, i);
			else if (r->type == OUTPUT_REDIRECT)
				fd = add_output_redirect(r, i);
			if (fd < 0)
			{
				redirect_error = true;
				break ;
			}
			r = r->next;
		}
		if (redirect_error)
		{
			ft_perror(r->filename);
			cmd_table_ptr = del_command(cmd_table_ptr);
			// need to delete exec_fd too!!!
			// might be best to just move exec_fds into command struct
		}
		else
		{
			cmd_table_ptr = cmd_table_ptr->next;
			i++;
		}
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
