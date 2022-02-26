/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <nic.flenghi@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:41:51 by fnichola          #+#    #+#             */
/*   Updated: 2021/04/13 09:51:33 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_strlcpy() and ft_strlcat() take the full size of the destination buffer and
 * guarantee NUL-termination if there is room.
 * Note that room for the NUL should be included in dstsize.
 *
 * Returns the total length of the string it tried to create
 * (the initial length of dst plus the length of src).
 *
 * If the return value is >= dstsize, the output string has been truncated.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_length;
	size_t	dst_length;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	src_length = ft_strlen(src);
	while (dst[i] && i < dstsize)
		i++;
	dst_length = i;
	while (i + 1 < dstsize && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (i < dstsize)
		dst[i] = 0;
	return (dst_length + src_length);
}
