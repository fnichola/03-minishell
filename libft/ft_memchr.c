/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <nic.flenghi@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 06:30:57 by nic               #+#    #+#             */
/*   Updated: 2021/04/18 12:46:13 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_memchr() function scans the initial n bytes of the memory area
 * pointed to by s for the first instance of c.
 * Both c and the bytes of the memory area pointed to by s are interpreted
 * as unsigned char.
 *
 * Returns a pointer to the matching byte or NULL if the character does not
 * occur in the given memory area.
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
