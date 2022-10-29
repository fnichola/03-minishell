/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 02:43:15 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/29 13:32:51 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// test+=bob
t_envlist	split_env(const char *str)
{
	size_t		i;
	t_envlist	new_var;
	char		*tmp;

	i = 1;
	new_var.name = NULL;
	new_var.value = NULL;
	if (!ft_isalpha(str[0]))
	{
		ft_puterror("export", str, "not a valid identifier");
	}
	else
	{
		while (ft_isalnum(str[i]))
			i++;
		new_var.name = ft_wsubstr(str, 0, i);
		if (str[i] == '+' && str[i + 1] == '=')
		{
			tmp = ft_wsubstr(str, i + 2, ft_strlen(str));
			new_var.value = ft_wstrjoin(ft_getenv(new_var.name), tmp);
			free(tmp);
		}
		else if (str[i] == '=')
			new_var.value = ft_wsubstr(str, i + 1, ft_strlen(str));
		else
		{
			free(new_var.name);
			new_var.name = NULL;
			ft_puterror("export", str, "not a valid identifier");
		}
	}
	return (new_var);
}
