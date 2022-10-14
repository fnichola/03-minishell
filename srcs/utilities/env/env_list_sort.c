/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:10:16 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 06:00:10 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*env_list_sort(t_envlist *env_list)
{
	bool		is_sorted;
	t_envlist	*ptr;

	is_sorted = false;
	ptr = env_list;
	if (!ptr || !ptr->next)
		return (NULL);
	while (!is_sorted)
	{
		is_sorted = true;
		ptr = env_list_first(ptr);
		while (ptr && ptr->next)
		{
			if (ft_strcmp(ptr->name, ptr->next->name) > 0)
			{
				env_list_swap_next(ptr);
				is_sorted = false;
			}
			if (ptr->next)
				ptr = ptr->next;
		}
	}
	return (env_list_first(ptr));
}
