/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:10:54 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 05:48:45 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*env_list_dup(t_envlist *node)
{
	t_envlist	*new_node;
	char		*name;
	char		*value;
	char		*string;

	name = ft_wstrdup(node->name);
	value = ft_wstrdup(node->value);
	string = ft_wstrdup(node->string);
	new_node = env_list_new(name, value, string);
	new_node->export = node->export;
	return (new_node);
}
