/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 05:44:22 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 05:44:38 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*ft_unsetenv(t_envlist *e_list, char *unset_key)
{
	t_envlist	*tmp;
	t_envlist	*prev;

	tmp = e_list->next;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, unset_key) == 0)
		{
			if (prev == NULL)
				e_list = tmp;
			else
				prev->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (e_list);
}
