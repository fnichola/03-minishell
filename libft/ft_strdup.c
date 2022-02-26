/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <nic.flenghi@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 09:37:31 by fnichola          #+#    #+#             */
/*   Updated: 2021/04/13 09:44:48 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	size;

	size = ft_strlen(s) + 1;
	ret = (char *)malloc(size);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, size);
	return (ret);
}
