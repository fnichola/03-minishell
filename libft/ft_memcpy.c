/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <nic.flenghi@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:29:27 by fnichola          #+#    #+#             */
/*   Updated: 2021/04/18 12:29:32 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The  ft_memcpy()  function  copies  n bytes from memory area src to memory
 * area dest.
 * The memory areas must not overlap.
 * Use ft_memmove if the memory areas do overlap.
 * RETURN: a pointer to dest
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;

	if (n == 0 || dest == src)
		return (dest);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
