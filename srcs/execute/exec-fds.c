/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec-fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:58:36 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/11 23:42:25 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	alloc_exec_fds(void)
{
	size_t	i;

	g_data.exec_fds = malloc_error_check(sizeof(int *) * (g_data.num_cmds + 1));
	i = 0;
	// printf("g_data.num_cmds %zu\n",g_data.num_cmds);
	while (i < g_data.num_cmds)
	{
		printf("alloc %zu\n\n", g_data.redirect->count_cmds);
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
		g_data.redirect = g_data.redirect->next;
		printf("create_pipe\n\n\n");
		// printf("g_data.exec_fds[%zu- 1][1] %d\n", i ,g_data.exec_fds[i - 1][1]);
		ft_wpipe(pipe_fd);
		if (g_data.exec_fds[i - 1][1] == STDOUT_FILENO)//parser_functionsでopenしたファイルのfdが入っている時は初期化したくないので、
			(g_data.exec_fds[i - 1])[1] = pipe_fd[1];//ここで代入しなかったfdはcloseしなければでは？
		else
		{//parser_redirect()でopen()したfdを割り当てる時に入る.
			// printf("g_data.redirect->fd; %d\n\n\n", g_data.redirect->fd);
			printf("else\n\n");
			printf("g_data.redirect->fd %d\n", g_data.redirect->fd);
			// printf("g_data.redirect->count_cmds - 1 %lu\n", g_data.redirect->count_cmds - 1); //g_data.redirectの更新がうまく行っていない。
			g_data.exec_fds[g_data.redirect->count_cmds - 1][1] = g_data.redirect->fd;// ここで
			// printf("g_data.redirect->fd %d\n", g_data.redirect->fd);//ここでopenしたfdが更新されていないのがわかる。
			g_data.redirect = g_data.redirect->next;
			
		}
		if (g_data.exec_fds[i][0] == STDIN_FILENO)
			(g_data.exec_fds[i])[0] = pipe_fd[0];
		printf("g_data.exec_fds[%zu- 1][1] %d\n", i , g_data.exec_fds[i - 1][1]);
		i++;
	}
	i--;
	(g_data.exec_fds[i])[1] = STDOUT_FILENO;
}

void	init_exec_fds(void)
{
	alloc_exec_fds();
	if (g_data.num_cmds == 1)
	{
		printf("init_exec_fds\n");
		// printf("g_data.num_cmds %zu\n", g_data.num_cmds);
		(g_data.exec_fds[0])[0] = STDIN_FILENO;//ここをg_data.exec_fds[1]から[0]に変更しましたが、なぜ1だったのでしょうか？
		(g_data.exec_fds[0])[1] = STDOUT_FILENO;
		printf("init_exec_fds end\n");
	}
	else
		create_pipes();
}
