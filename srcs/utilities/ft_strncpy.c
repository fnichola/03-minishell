/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 03:52:54 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 03:53:21 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncpy(char *dest, char *src, size_t cpy_len)
{
	size_t	i;

	i = 0;
	if (!src)
	{
		exit_error("strncpy error\n");
		return (-1);
	}
	while (i < cpy_len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (0);
}
