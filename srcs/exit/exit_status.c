/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:00:00 by akihito           #+#    #+#             */
/*   Updated: 2022/10/30 14:29:01 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void signal_handler_child(int signo)
{
	(void)signo;
	exit(130);
}

void	set_status_from_child_status(int wstatus)
{
	if (WIFEXITED(wstatus))//ここに入るとexit_statusが変な値になる。
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
