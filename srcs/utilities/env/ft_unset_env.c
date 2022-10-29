/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 05:44:22 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/29 10:16:28 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unsetenv(char *unset_key)
{
	t_envlist	*tmp;

	tmp = ft_findenv(unset_key);
	if (tmp)
	{
		free(tmp->name);
		free(tmp->value);
		free(tmp->string);
		if (tmp->prev)
		{
			tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
		}
		else
		{
			g_data.env_list = tmp->next;
			if (tmp->next)
				tmp->next->prev = NULL;
		}
		free (tmp);
	}
}
