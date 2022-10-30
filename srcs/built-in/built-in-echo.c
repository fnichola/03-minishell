/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in-echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:41:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 11:42:12 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_echo(char **argv)
{
	int		option;
	size_t	arg_i;

	debug_log("built_in_echo\n");
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
	debug_log("built_in_echo g_data.exit_status %d\n", g_data.exit_status);
	if (!option)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_data.exit_status = 0;
}
