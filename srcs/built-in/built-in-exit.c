/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in-exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:45:45 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 13:31:16 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_exit_status(char	*num)
{
	int	i;

	i = 0;
	while (num[i] != '\0')
	{
		if (!ft_isdigit(num[i]))
			return (false);
		i++;
	}
	return (true);
}

void	exit_and_free_command(int exit_status)
{
	free_command_table();
	exit(exit_status);
}

void	built_in_exit(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	free_env_list(&g_data.env_list);
	ft_putendl_fd("exit", 1);
	if (argc == 2)
	{
		if (!is_valid_exit_status(argv[1]))
		{
			ft_puterror("exit", argv[1], "numeric argument required");
			g_data.exit_status = 255;
		}
		else
			g_data.exit_status = ft_atoi(argv[1]);
	}
	else if (argc > 2)
	{
		ft_puterror("exit", "too many arguments\n", NULL);
		g_data.exit_status = 1;
	}
	exit_and_free_command(g_data.exit_status);
}
