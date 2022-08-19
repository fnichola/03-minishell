/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:54:35 by akihito           #+#    #+#             */
/*   Updated: 2022/08/08 20:05:08 by akihito          ###   ########.fr       */
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
		g_data->env_list = ft_unsetenv(g_data->elst, argv[i]);
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
		if (ft_strcmp(tmp->key, unset_key) == 0)
		{
			if (prev == NULL)
				e_list = tmp;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (e_list);
}
