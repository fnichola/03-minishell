/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:00:00 by akihito           #+#    #+#             */
/*   Updated: 2022/10/23 22:52:08 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_status_from_child_status(int wstatus)
{
	debug_log("set_status_from_child_status 2 %d\n\n", wstatus);
	if (WIFEXITED(wstatus))//ここに入るとexit_statusが変な値になる。
	{
		debug_log("exited %d\n\n", wstatus);
		if (!!WEXITSTATUS(wstatus))
			printf("WEXITSTATUS(wstatus)");
		g_data.exit_status = WEXITSTATUS(wstatus);
		debug_log(" set_status_from_child_status g_data.exit_status %d\n", g_data.exit_status);
	}
	else if (!WIFSIGNALED(wstatus))
	{
		// debug_log("set_status_from_child_status 3\n");
		debug_log("signaled\n\n");
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_data.exit_status = WTERMSIG(wstatus) + 128;
		debug_log("g_data.exit_status %d\n\n\n", g_data.exit_status);
	}
}
