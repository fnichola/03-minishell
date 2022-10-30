/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:20:00 by akihito           #+#    #+#             */
/*   Updated: 2022/10/30 14:30:45 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

// void sig_handler(int signum)
// {
// 	printf("signum %d\n", signum);
	
// }

void	signal_handler(int signo)
{
	g_data.exit_status = 128 + signo;
	g_data.sig_int = true;
	// ft_putchar_fd('\n', STDOUT_FILENO);
	// rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
}
