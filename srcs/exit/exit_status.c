/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:00:00 by akihito           #+#    #+#             */
/*   Updated: 2022/10/26 14:16:57 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void signal_handler_child(int signo)
{
	(void)signo;
	debug_log("signal_handler_child\n");
	exit(130);
}

void	set_status_from_child_status(int wstatus)
{
	debug_log("set_status_from_child_status 2 %d\n\n", wstatus);
	if (WIFEXITED(wstatus))//ここに入るとexit_statusが変な値になる。
	{
		debug_log("exited %d\n\n", wstatus);
		if (!!WEXITSTATUS(wstatus))
			debug_log("WEXITSTATUS(wstatus)");
		g_data.exit_status = WEXITSTATUS(wstatus);
		debug_log(" set_status_from_child_status g_data.exit_status %d\n", g_data.exit_status);
	}
	else if (WIFSIGNALED(wstatus))
	{
		debug_log("set_status_from_child_status 3\n");
		debug_log("signaled wstatus %d\n\n", wstatus);
		if (wstatus == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3", STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_data.exit_status = WTERMSIG(wstatus) + 128;
		debug_log("g_data.exit_status %d\n\n\n", g_data.exit_status);
	}
}
