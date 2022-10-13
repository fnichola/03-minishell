/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 03:59:52 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 05:36:57 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_envlist **env_list)
{
	t_envlist	*ptr;
	t_envlist	*tmp;

	ptr = *env_list;
	while (ptr)
	{
		free(ptr->name);
		free(ptr->value);
		free(ptr->string);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	*env_list = NULL;
}
