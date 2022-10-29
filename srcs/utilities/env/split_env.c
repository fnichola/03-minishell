/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 02:43:15 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/29 19:40:04 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	split_env(const char *str)
{
	size_t		i;
	t_envlist	new_var;
	t_envlist	*add_var;
	char		*add_value;
	i = 0;
	// new_var = (t_envlist)malloc(sizeof(t_envlist));
	printf("str = %s\n", str);
	while (str[i])
	{
		if (i > 1 && str[i] == '=')
		{
			if (str[i - 1] == '+')
			{
				add_var = (t_envlist *)malloc(sizeof(t_envlist));
				add_value = ft_wstrdup(ft_wsubstr(str, 0, i-1));
				printf("ft_wsubstr(str, 0, i-1) %s\n", ft_wsubstr(str, i+1, ft_strlen(str)-i));
				printf("ft_wsubstr(str, 0, i+1) %s\n",ft_wsubstr(str, 0, i-1) );
				add_var = ft_findenv(add_value);
				if (add_var)
					add_var->value = ft_wstrjoin(add_var->value, ft_wsubstr(str, i+1, ft_strlen(str)-i));
				printf("new_var.name = %s\n",  add_var->name);
				printf("new_var.value = %s\n",  add_var->value);
				new_var.name = add_var->name;
				new_var.value = ft_wstrjoin(add_var->value, &str[i + 1]);
				printf("new_var.value %s\n", new_var.value);
			}
			else
			{
				new_var.name = ft_wsubstr(str, 0, i);
				new_var.value = ft_wstrdup(&str[i + 1]);
			}
			printf("return\n");
			debug_log("split_env: new_var.name = %s\nnew_var.value = %s\n", new_var.name, new_var.value);
			return (new_var);
		}
		i++;
	}
	new_var.name = NULL;
	new_var.value = NULL;
	return (new_var);
}
