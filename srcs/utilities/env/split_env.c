/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 02:43:15 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 03:47:14 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	split_env(const char *str)
{
	size_t		i;
	t_envlist	new_var;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			new_var.name = ft_wsubstr(str, 0, i);
			new_var.value = ft_wstrdup(&str[i + 1]);
			debug_log("split_env: new_var.name = %s\nnew_var.value = %s\n", new_var.name, new_var.value);
			return (new_var);
		}
		i++;
	}
	new_var.name = NULL;
	new_var.value = NULL;
	return (new_var);
}
