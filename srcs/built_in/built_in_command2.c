/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:54:35 by akihito           #+#    #+#             */
/*   Updated: 2022/10/13 08:35:35 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

void	builtin_unset(char **argv)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		g_data.env_list = ft_unsetenv(g_data.env_list, argv[i]);
		i++;
	}
	// g_status = 0;
	return ;
}

void	free_command_table(void *ptr)
{
	size_t		i;
	t_command	*command;

	command = (t_command *)ptr;
	i = 0;
	while (command->argv && command->argv[i])
	{
		free(command->argv[i]);
		i++;
	}
	free(command->argv);
	free_redirects(&command->redirects);
	free(command);
}

void	built_in_exit(char **argv)
{
	int	ret;
	int	argc;

	argc = 0;
	while (argv[argc])
		argc++;

	ft_lstclear(&g_data.command_table, free_command_table);
	free_env_list(&g_data.env_list);
	if (argc == 1)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else if (argc == 2)
	{
		printf("exit\n");
		ret = ft_atoi(argv[1]);
		exit(ret);
	}
	else
	{
		printf("too many arguments\n"); //need a separate error function
	}
}
