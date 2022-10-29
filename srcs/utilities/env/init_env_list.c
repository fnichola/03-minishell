/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:02:02 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/29 10:02:47 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env_list(char **envp)
{
	size_t		i;
	char		*name;
	char		*value;
	t_envlist	*new_var;

	i = 0;
	while (envp[i])
	{
		name = get_env_name(envp[i]);
		value = get_env_value(envp[i]);
		new_var = env_list_new(name, value, ft_strdup(envp[i]));
		env_list_add_back(&g_data.env_list, new_var);
		new_var->export = true;
		i++;
	}
}
