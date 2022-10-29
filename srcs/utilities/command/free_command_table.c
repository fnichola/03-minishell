/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 02:54:07 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/18 01:12:35 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command_table(void)
{
	t_command	*ct;
	t_command	*tmp;

	ct = g_data.command_table;
	while(ct)
	{
		tmp = ct->next;
		free_command(ct);
		ct = tmp;
	}
	g_data.command_table = NULL;
}
