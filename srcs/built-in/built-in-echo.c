/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in-echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:41:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 18:09:15 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_echo(char **argv)
{
	int		option;
	size_t	arg_i;

	option = 0;
	arg_i = 1;
	if (argv[1] && ft_strncmp(argv[arg_i], "-n", 2) == 0)
	{
		arg_i++;
		while (ft_strncmp(argv[arg_i], "-n", 2) == 0)
			arg_i++;
		option++;
	}
	while (argv[arg_i])
	{
		ft_putstr_fd(argv[arg_i], STDOUT_FILENO);
		if (argv[arg_i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		arg_i++;
	}
	if (!option)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_data.exit_status = 0;
}
