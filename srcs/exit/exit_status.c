/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:00:00 by akihito           #+#    #+#             */
/*   Updated: 2022/10/30 16:43:48 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_child(int signo)
{
	(void)signo;
	exit(130);
}

void	set_status_from_child_status(int wstatus)
{
	if (WIFEXITED(wstatus))
	{
		g_data.exit_status = WEXITSTATUS(wstatus);
	}
	else if (WIFSIGNALED(wstatus))
	{
		if (wstatus == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3", STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_data.exit_status = WTERMSIG(wstatus) + 128;
	}
}
