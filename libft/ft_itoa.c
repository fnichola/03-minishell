/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <nic.flenghi@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 11:36:43 by fnichola          #+#    #+#             */
/*   Updated: 2021/04/17 12:55:38 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long num, long *div)
{
	int	digits;

	digits = 0;
	while (num / *div != 0)
	{
		*div *= 10;
		digits++;
	}
	*div /= 10;
	if (num <= 0)
		digits += 1;
	return (digits);
}

static char	*make_str(char *ret, int digits, long *div, long num)
{
	int	i;

	i = 0;
	if (num < 0)
	{
		ret[i++] = '-';
		num *= -1;
	}
	if (num == 0)
		ret[i++] = '0';
	else
	{
		while (i < digits)
		{
			ret[i] = num / *div + '0';
			num = num % *div;
			*div /= 10;
			i++;
		}
	}
	ret[i] = '\0';
	return (ret);
}

/**
 * Allocates (with malloc(3)) and returns a string representing the integer
 * received as an argument. Negative numbers must be handled.
*/
char	*ft_itoa(int n)
{
	char	*ret;
	int		digits;
	long	div;
	long	num;

	div = 1;
	num = (long)n;
	digits = count_digits(num, &div);
	ret = malloc(digits + 1);
	if (!ret)
		return (NULL);
	ret = make_str(ret, digits, &div, num);
	return (ret);
}
