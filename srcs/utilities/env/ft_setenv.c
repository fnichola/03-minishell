/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:05:48 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 14:30:53 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	overwrite_env(t_envlist *node, const char *name, const char *value)
{
	free(node->value);
	if (value)
		node->value = ft_wstrdup(value);
	free(node->string);
	node->string = env_to_string(name, value);
}

static void	create_env(const char *name, const char *value)
{
	t_envlist	*new_node;

	if (value)
	{
		new_node = env_list_new(ft_wstrdup(name), ft_wstrdup(value), NULL);
		env_list_add_back(&g_data.env_list, new_node);
	}
	else
	{
		new_node = env_list_new(ft_wstrdup(name), NULL, NULL);
		env_list_add_back(&g_data.env_list, new_node);
	}
}

/**
 * Add or update an env variable.
 * If a variable with "name" doesn't exist it will be created.
 * If "name" exists and overwrite != 0 its value will be udpated.
 * Returns -1 if there are invalid parameters.
 */
int	ft_setenv(const char *name, const char *value, int overwrite)
{
	t_envlist	*node;

	node = ft_findenv(name);
	if (!name || !ft_strlen(name) || ft_strchr(name, '='))
	{
		errno = EINVAL;
		return (-1);
	}
	else if (node && overwrite)
		overwrite_env(node, name, value);
	else if (!node)
		create_env(name, value);
	return (0);
}
