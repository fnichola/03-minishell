/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:55:31 by atomizaw          #+#    #+#             */
/*   Updated: 2022/10/30 14:38:49 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_g_data(void)
{
	g_data.command_table = NULL;
	return ;
}

void	inits(char **envp)
{	
	init_env_list(envp);
	init_g_data();
	init_built_in_table();
	return ;
}
