/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:54:35 by akihito           #+#    #+#             */
/*   Updated: 2022/10/29 09:25:17 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

void	built_in_unset(char **argv)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		g_data.env_list = ft_unsetenv(g_data.env_list, argv[i]);
		i++;
	}
	g_data.exit_status = 0;
}

void	built_in_exit(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc])
	{
		debug_log("argv[%d] %s\n",argc, argv[argc]);
		argc++;
	}
	free_env_list(&g_data.env_list);
	ft_putendl_fd("exit", 1);
	if (argv[1] == NULL)//ただのexit
	{
		// ft_putendl_fd("exit", 1);
		exit(g_data.exit_status);
	}
	if (argc == 2)// exit 4など
	{
		debug_log("test\n\n");
		if (!is_valid_exit_status(argv[1]))
		{
			debug_log("test\n\n");
			ft_puterror("exit", argv[1], "numeric argument required");
			g_data.exit_status = 255;
		}
		else
			g_data.exit_status = ft_atoi(argv[1]);
	}
	else//exit 4 2 1など
	{
		ft_puterror("exit","too many arguments\n", NULL); //need a separate error function
		g_data.exit_status = 1;
	}
	exit_and_free_command(g_data.exit_status);
}

bool	is_valid_exit_status(char	*num)
{
	int	i;

	i = 0;
	while(num[i] != '\0')
	{
		if(!ft_isdigit(num[i]))
			return (false);
		i++;
	}
	return(true);
}

void	exit_and_free_command(int exit_status)
{
	free_command_table();
	exit(exit_status);
}
