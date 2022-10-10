/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec-fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:58:36 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/10 23:58:41 by akihito          ###   ########.fr       */
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

static void	create_pipes(void)
{
	size_t	i;
	int		pipe_fd[2];

	(g_data.exec_fds[0])[0] = STDIN_FILENO;
	i = 1;//1つ目のSTDINはいらないから
	printf("num_cmds %zu\n", g_data.num_cmds);
	while (i < g_data.num_cmds)
	{
		printf("create_pipe\n\n\n");
		ft_wpipe(pipe_fd);
		if (g_data.exec_fds[i - 1][1] == STDOUT_FILENO)//parser_functionsでopenしたファイルのfdが入っている時は初期化したくないので、
			(g_data.exec_fds[i - 1])[1] = pipe_fd[1];//ここで代入しなかったfdはcloseしなければでは？
		else
		{//parser_redirect()でopen()したfdを割り当てる時に入る.
			// printf("g_data.redirect->fd; %d\n\n\n", g_data.redirect->fd);
			g_data.exec_fds[g_data.redirect->count_cmds - 1][1] = g_data.redirect->fd;// ここで
			g_data.redirect = g_data.redirect->next;
		}
		if (g_data.exec_fds[i][0] == STDIN_FILENO)
			(g_data.exec_fds[i])[0] = pipe_fd[0];
		printf("g_data.exec_fds[i - 1][1] %d\n", g_data.exec_fds[i - 1][1]);
		i++;
	}
	// i = 0;
    // while (i < g_data.num_cmds)
    // {
    //     printf("exec_fds[%zu]: (%d, %d)\n", i, (g_data.exec_fds[i])[0], (g_data.exec_fds[i])[1]);
    //     i++;
    // }
	i--;
	(g_data.exec_fds[i])[1] = STDOUT_FILENO;
}

void	init_exec_fds(void)
{
	alloc_exec_fds();
	if (g_data.num_cmds == 1)
	{
		printf("init_exec_fds\n");
		(g_data.exec_fds[0])[0] = STDIN_FILENO;
		(g_data.exec_fds[0])[1] = STDOUT_FILENO;
	}
	else
		create_pipes();
}
