/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init-built-in-table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:23:49 by akihito           #+#    #+#             */
/*   Updated: 2022/10/30 12:21:18 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_built_in_table(void)
{
	const t_str_func_table	temp[] = {
	{"echo",	&built_in_echo},
	{"cd",		&built_in_cd},
	{"pwd",		&built_in_pwd},
	{"env",		&built_in_env},
	{"export",	&built_in_export},
	{"exit",	&built_in_exit},
	{"unset",	&built_in_unset},
	};
	t_str_func_table		*built_ins;

	built_ins = malloc_error_check(sizeof(temp));
	g_data.num_built_ins = sizeof(temp) / sizeof(t_str_func_table);
	ft_memcpy(built_ins, temp, sizeof(temp));
	g_data.built_ins = built_ins;
}
