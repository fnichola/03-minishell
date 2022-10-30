/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 22:20:34 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 17:31:07 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Convert ASCII string to integer.
 * Ignores spaces in the beginning, can handle one optional + or -.
 * If input is greater than INT_MAX or less than INT_MIN, returns -1 or 0
 * respectively and sets err to true.
 */
int	ft_atoi_err(const char *nptr, bool *err)
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
		{
			*err = true;
			return (0);
		}
		if (result > (unsigned long long)LLONG_MAX && sign == 1)
		{
			*err = true;
			return (-1);
		}
	}
	return ((int)result * sign);
}
