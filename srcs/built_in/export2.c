/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 01:57:05 by akihito           #+#    #+#             */
/*   Updated: 2022/10/29 19:21:26 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// this check needs to be fixed!
bool	is_valid_variable(char *variable)
{
	size_t	i;
	char	*name;

	i = 0;
	while (variable[i])
	{
		if (variable[i] == '=' && variable[i-1] == '+')
			name = ft_wsubstr(variable, 0, i - 1);
		else if (variable[i] == '=')
			name = ft_wsubstr(variable, 0, i);
		i++;
	}
	i = 0;
	printf("name = %s\n", name);
	if (!ft_isdigit(name[0]))
	{
		while (name[i])
		{
			printf("variable[i] = %c\n", name[i]);
			if (!ft_isalnum(name[i++]))
				return (0);
		}
		return (1);
	}
	return (0);
}
