/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 02:43:15 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 19:15:05 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_and_join_env(t_envlist *new_var, const char *str)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	(*new_var).name = ft_wsubstr(str, 0, i);
	if (str[i] == '+' && str[i + 1] == '=')
	{
		tmp = ft_wsubstr(str, i + 2, ft_strlen(str));
		(*new_var).value = ft_wstrjoin(ft_getenv((*new_var).name), tmp);
		free(tmp);
	}
	else if (str[i] == '=')
		(*new_var).value = ft_wsubstr(str, i + 1, ft_strlen(str));
	else
	{
		free((*new_var).name);
		(*new_var).name = NULL;
		ft_puterror("export", str, "not a valid identifier");
	}
}

t_envlist	split_env(const char *str)
{
	t_envlist	new_var;

	new_var.name = NULL;
	new_var.value = NULL;
	if (!ft_isalpha(str[0]))
	{
		ft_puterror("export", str, "not a valid identifier");
	}
	else
	{
		split_and_join_env(&new_var, str);
	}
	return (new_var);
}
