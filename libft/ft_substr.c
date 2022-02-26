/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <nic.flenghi@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 21:13:24 by fnichola          #+#    #+#             */
/*   Updated: 2021/04/17 12:49:04 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocates (with malloc(3)) and returns a substring from the string ’s’.
 * The substring begins at index ’start’ and is of maximum size ’len’.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;
	size_t	size;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	size = len + 1;
	if (start >= str_len)
		size = 1;
	else if ((str_len - start) < len)
		size = str_len - start + 1;
	sub = (char *)malloc(size);
	if (!sub)
		return (NULL);
	i = 0;
	j = start;
	while (i < (size - 1) && s[j])
		sub[i++] = s[j++];
	sub[i] = 0;
	return (sub);
}
