/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 02:54:07 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 14:39:40 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command_table(void)
{
	t_command	*ct;
	t_command	*tmp;

	ct = g_data.command_table;
	while (ct)
	{
		tmp = ct->next;
		free_command(ct);
		ct = tmp;
	}
	g_data.command_table = NULL;
}
