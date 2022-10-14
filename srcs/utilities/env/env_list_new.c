/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:04:43 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 04:05:06 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Make a new t_envlist node.
 * The node can be made with name and value strings or with a raw env string
 * ("NAME=VALUE").
 * 
 * For convenience it can be called in three different ways,
 * NULL parameters will be auto-generated:
 * new_env = env_list_new(name, value, NULL);
 * new_env = env_list_new(NULL, NULL, string);
 * new_env = env_list_new(name, value, string);
 */
t_envlist	*env_list_new(char *name, char *value, char *string)
{
	t_envlist	*new;

	new = malloc_error_check(sizeof(t_envlist));
	if (!name && !value && string)
	{
		name = get_env_name(string);
		value = get_env_value(string);
	}
	if (!string)
	{
		string = env_to_string(name, value);
	}
	if (!name)
	{
		free(new);
		return (NULL);
	}
	new->name = name;
	new->value = value;
	new->string = string;
	new->next = NULL;
	new->prev = NULL;
	new->export = false;
	return (new);
}
