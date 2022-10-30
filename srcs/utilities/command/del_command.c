/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 02:51:00 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 14:30:50 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Delete a single command from the command_table
 */
t_command	*del_command(t_command *cmd)
{
	t_command	*new_ptr;

	if (!cmd)
		return (NULL);
	if (cmd->prev)
		cmd->prev = cmd->next;
	if (cmd->next)
		cmd->next->prev = cmd->prev;
	new_ptr = cmd->next;
	if (cmd == g_data.command_table)
		g_data.command_table = new_ptr;
	free_command(cmd);
	return (new_ptr);
}
