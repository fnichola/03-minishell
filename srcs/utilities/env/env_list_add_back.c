/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_add_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:00:35 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 05:59:42 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*env_list_add_back(t_envlist **env_list, t_envlist *new_node)
{
	t_envlist	*last_node;

	if (!*env_list)
		*env_list = new_node;
	else
	{
		last_node = env_list_last(*env_list);
		new_node->prev = last_node;
		last_node->next = new_node;
	}
	return (new_node);
}
