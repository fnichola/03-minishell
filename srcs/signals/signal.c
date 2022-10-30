/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:20:00 by akihito           #+#    #+#             */
/*   Updated: 2022/10/30 19:51:57 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void	signal_handler(int signo)
{
	(void)signo;
	g_data.exit_status = 1;
	g_data.sig_int = true;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler_child(int signo)
{
	(void)signo;
	exit(128 + signo);
}


void	signal_handler_parent(int signo)
{
	(void)signo;
	g_data.exit_status = 1;
	g_data.sig_int = true;
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler_heredoc(int signo)
{
	(void)signo;
	g_data.exit_status = 1;
	g_data.sig_int = true;
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
}
