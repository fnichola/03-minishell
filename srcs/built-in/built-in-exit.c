/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in-exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:45:45 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 19:15:19 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_exit_status(char	*num)
{
	int		i;
	bool	is_valid;
	bool	err;

	i = 1;
	is_valid = true;
	if (!ft_isdigit(num[0]) && num[0] != '-')
		is_valid = false;
	else
	{
		while (num[i] != '\0')
		{
			if (!ft_isdigit(num[i]))
				is_valid = false;
			i++;
		}
	}
	err = false;
	ft_atoi_err(num, &err);
	if (err)
		is_valid = false;
	return (is_valid);
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
	if (argc > 1 && !is_valid_exit_status(argv[1]))
	{
		ft_puterror("exit", argv[1], "numeric argument required");
		g_data.exit_status = 255;
		exit_and_free_command(g_data.exit_status);
	}
	else if (argc > 2)
	{
		ft_puterror("exit", "too many arguments", NULL);
		g_data.exit_status = 1;
	}
	else
	{
		if (argc > 1)
			g_data.exit_status = (unsigned char)ft_atoi(argv[1]);
		exit_and_free_command(g_data.exit_status);
	}
}
