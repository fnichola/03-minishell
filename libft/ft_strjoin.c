/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <nic.flenghi@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 21:50:12 by fnichola          #+#    #+#             */
/*   Updated: 2021/04/17 12:51:33 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocates (with malloc(3)) and returns a newstring,
 * which is the result of the concatenation of ’s1’ and ’s2’.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	size;

	if (s1 && s2)
	{
		size = ft_strlen(s1) + ft_strlen(s2) + 1;
		ret = (char *)malloc(sizeof(char) * size);
		if (!ret)
			return (NULL);
		ft_strlcpy(ret, s1, size);
		ft_strlcat(ret, s2, size);
		return (ret);
	}
	return (NULL);
}
