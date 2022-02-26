/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:02:47 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/24 21:42:28 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_num(long num)
{
	long	div;
	int		ret;
	char	c;

	div = 1;
	ret = 0;
	while ((num / div) > 9)
		div *= 10;
	while (div >= 1)
	{
		c = (num / div) + '0';
		ret += write(1, &c, 1);
		num = num % div;
		div /= 10;
	}
	return (ret);
}

/**
 * Print a signed int.
 * RETURN:
 * Number of characters printed.
 */

int	ft_print_num(int nbr)
{
	long	num;
	int		ret;

	num = (long)nbr;
	ret = 0;
	if (num < 0)
	{
		ret += write(1, "-", 1);
		num *= -1;
	}
	if (num == 0)
		ret += write(1, "0", 1);
	else
		ret += write_num(num);
	return (ret);
}
