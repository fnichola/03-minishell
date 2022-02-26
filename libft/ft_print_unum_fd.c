/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:55:27 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/24 21:53:14 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Print an unsigned number using provided digits (e.g. "0123456789").
 * If truncate is true the number will be truncated to an unsigned int.
 * RETURN:
 * Number of characters printed.
 */

int	ft_print_unum_fd(int fd, unsigned long num, char *digits, int truncate)
{
	unsigned long	div;
	int				ret;
	int				base;

	if (truncate)
		num = (unsigned long)((unsigned int)(num));
	ret = 0;
	div = 1;
	base = ft_strlen(digits);
	while ((num / div) > (unsigned long)(base - 1))
		div *= base;
	if (num == 0)
		ret += write(fd, &digits[0], 1);
	else
	{
		while (div >= 1)
		{
			ret += write(fd, &digits[(num / div)], 1);
			num = num % div;
			div /= base;
		}
	}
	return (ret);
}
