/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <nic.flenghi@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 09:37:25 by fnichola          #+#    #+#             */
/*   Updated: 2021/04/13 09:52:25 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_calloc() function contiguously allocates enough space for count
 * objects that are size bytes of memory each and returns a pointer to the
 * allocated memory.  The allocated memory is filled with bytes of value zero.
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	if (size > 0)
		if (count > (((size_t)(-1)) / size))
			return (NULL);
	ret = malloc(count * size);
	if (!ret)
		return (NULL);
	ft_bzero(ret, count * size);
	return (ret);
}
