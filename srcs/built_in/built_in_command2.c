/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:54:35 by akihito           #+#    #+#             */
/*   Updated: 2022/10/11 06:04:15 by fnichola         ###   ########.fr       */
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

t_envlist	*ft_unsetenv(t_envlist *e_list, char *unset_key)
{
	t_envlist	*tmp;
	t_envlist	*prev;

	tmp = e_list->next;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, unset_key) == 0)
		{
			if (prev == NULL)
				e_list = tmp;
			else
				prev->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (e_list);
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
	if (command->input_redirect)
	{
		free(command->input_redirect->filename);
		free(command->input_redirect);
	}
	if (command->output_redirect)
	{
		free(command->output_redirect->filename);
		free(command->output_redirect);
	}
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
