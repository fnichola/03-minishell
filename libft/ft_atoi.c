/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 22:20:34 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/05 16:30:32 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Convert ASCII string to integer.
 * Ignores spaces in the beginning, can handle one optional + or -.
 * If input is greater than INT_MAX or less than INT_MIN, returns -1 or 0
 * respectively.
*/
int	ft_atoi(const char *nptr)
{
	unsigned long long	result;
	int					sign;

	result = 0;
	sign = 1;
	while ((*nptr >= '\t' && *nptr <= '\r') || (*nptr == ' '))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*(nptr++) == '-')
			sign = -1;
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + *(nptr++) - '0';
		if (result > ((unsigned long long)LLONG_MAX + 1) && sign == -1)
			return (0);
		if (result > (unsigned long long)LLONG_MAX && sign == 1)
			return (-1);
	}
	return ((int)result * sign);
}
