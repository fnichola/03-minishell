/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:06:34 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/29 19:39:47 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Find an env variable and return a pointer to it's node.
 * Use ft_getenv to retrieve the value directly.
 */
t_envlist	*ft_findenv(const char *name)
{
	t_envlist	*tmp;

	tmp = g_data.env_list;
	while (tmp)
	{
		if (is_str_match(tmp->name, name))
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
