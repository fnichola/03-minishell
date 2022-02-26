/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nic <nic@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 07:10:53 by nic               #+#    #+#             */
/*   Updated: 2021/04/11 07:13:37 by nic              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The strrchr() function locates the LAST occurrence of c (converted to char)
 * in the string pointed to by s.  The terminating nul character is considered
 * to be part of the string;
 * therefore if c is `\0', the function locates the terminating `\0'.
*/
char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s) + 1;
	while (i-- > 0)
		if (s[i] == (char)c)
			return ((char *)(s + i));
	return (NULL);
}
