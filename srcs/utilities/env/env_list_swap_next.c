/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_swap_next.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:09:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 05:36:57 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_list_swap_next(t_envlist *node)
{
	t_envlist	*tmp1;
	t_envlist	*tmp2;

	tmp1 = node->prev;
	tmp2 = node->next->next;
	if (tmp1)
		tmp1->next = node->next;
	if (tmp2)
		tmp2->prev = node;
	node->next->prev = tmp1;
	node->next->next = node;
	node->prev = node->next;
	node->next = tmp2;
}
