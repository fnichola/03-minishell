/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <nic.flenghi@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 21:18:07 by fnichola          #+#    #+#             */
/*   Updated: 2021/04/13 13:04:39 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_strlcpy() and ft_strlcat() take the full size of the destination buffer
 * and guarantee NUL-termination if there is room.
 * Note that room for the NUL should be included in dstsize.
 *
 * Returns the total length of the string it tried to create (length of src)
 *
 * If the return value is >= dstsize, the output string has been truncated.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	length;

	if (!src)
		return (0);
	length = ft_strlen(src);
	if (dstsize == 0 || !dst)
		return (length);
	i = 0;
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	return (length);
}
