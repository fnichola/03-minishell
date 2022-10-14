/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:43:06 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/14 02:37:58 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_add_back(t_command *new_command)
{
	t_command	*ct;

	if (!new_command)
		return;
	ct = g_data.command_table;
	if (!ct)
	{
		g_data.command_table = new_command;
		return ;
	}
	while (ct->next)
		ct = ct->next;
	ct->next = new_command;
	new_command->prev = ct;
}
