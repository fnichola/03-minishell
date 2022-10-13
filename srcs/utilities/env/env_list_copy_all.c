/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_copy_all.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:10:36 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 05:48:55 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*env_list_copy_all(t_envlist *node)
{
	t_envlist	*new_list;

	new_list = NULL;
	while (node)
	{
		env_list_add_back(&new_list, env_list_dup(node));
		node = node->next;
	}
	return (new_list);
}
