/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <nic.flenghi@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:06:34 by fnichola          #+#    #+#             */
/*   Updated: 2021/04/17 12:55:44 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocates (with malloc(3)) and returns a copy of ’s1’
 * with the characters specified in ’set’ removed from
 * the beginning and the end of the string.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*ret;

	if (!s1)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1)
		s1++;
	if (*s1 == 0)
		return (ft_strdup(""));
	i = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]))
		i--;
	ret = (char *)malloc(i + 2);
	if (!ret)
		return (NULL);
	j = 0;
	while (j < i + 1)
	{
		ret[j] = s1[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
