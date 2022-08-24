/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tolower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:40:03 by fnichola          #+#    #+#             */
/*   Updated: 2022/08/24 11:40:27 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_tolower(char *str)
{
	char	*str_lower;
	size_t	i;

	str_lower = ft_strdup(str);
	i = 0;
	while (str_lower[i])
	{
		str_lower[i] = ft_tolower(str_lower[i]);
		i++;
	}
	return (str_lower);
}
