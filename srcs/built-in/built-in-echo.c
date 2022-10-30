/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in-echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:41:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 14:26:59 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_echo(char **argv)
{
	int		option;
	size_t	arg_i;

	option = 0;
	arg_i = 0;
	if (argv[arg_i] && ft_strcmp(argv[arg_i], "-n") == 0 && arg_i++)
		option++;
	while (argv[++arg_i])
	{
		ft_putstr_fd(argv[arg_i], STDOUT_FILENO);
		if (argv[arg_i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!option)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_data.exit_status = 0;
}
