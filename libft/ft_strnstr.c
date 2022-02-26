/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 07:37:08 by nic               #+#    #+#             */
/*   Updated: 2021/11/02 15:26:02 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Find the first occurrence of the null-terminated string little in the
 * string big, where not more than len characters are searched.
 * Characters that appear after a NULL character are not searched.
 *
 * If little is an empty string, big is returned;
 * if little occurs nowhere in big, NULL is returned;
 * otherwise a pointer to the first character of the first occurrence
 * of little is returned.
*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	while (i <= (len - little_len) && big[i] && len != 0 && little_len <= len)
	{
		j = 0;
		while (little[j])
		{
			if (big[i + j] == little[j])
				j++;
			else
				break ;
		}
		if (j == little_len)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
