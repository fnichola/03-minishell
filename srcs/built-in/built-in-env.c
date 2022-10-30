/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in-env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:43:36 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 11:43:49 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_env(char **argv)
{
	t_envlist	*per_env;

	(void)argv;
	per_env = g_data.env_list;
	while (per_env)
	{
		if (per_env->value)
			printf("%s=%s\n", per_env->name, per_env->value);
		per_env = per_env->next;
	}
	g_data.exit_status = 0;
}
