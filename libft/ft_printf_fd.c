/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:20:01 by fnichola          #+#    #+#             */
/*   Updated: 2021/11/14 21:20:08 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_char_fd(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

static int	ft_print_str_fd(int fd, char *s)
{
	int	ret;

	ret = 0;
	if (s)
		ret += write(fd, s, ft_strlen(s));
	else
		ret += write(fd, "(null)", 6);
	return (ret);
}

static int	eval_format(int fd, char conversion, va_list *ap)
{
	int	ret;

	ret = 0;
	if (conversion == 'c')
		ret += ft_print_char_fd(fd, va_arg(*ap, int));
	if (conversion == 's')
		ret += ft_print_str_fd(fd, va_arg(*ap, char *));
	if (conversion == 'p')
	{
		ret += write(fd, "0x", 2);
		ret += ft_print_unum_fd(fd, va_arg(*ap, unsigned long), HEX_LOWER, 0);
	}
	if (conversion == 'd' || conversion == 'i')
		ret += ft_print_num_fd(fd, va_arg(*ap, int));
	if (conversion == 'u')
		ret += ft_print_unum_fd(fd, va_arg(*ap, unsigned long), DEC, 1);
	if (conversion == 'x')
		ret += ft_print_unum_fd(fd, va_arg(*ap, unsigned long), HEX_LOWER, 1);
	if (conversion == 'X')
		ret += ft_print_unum_fd(fd, va_arg(*ap, unsigned long), HEX_UPPER, 1);
	if (conversion == '%')
		ret += write(fd, "%", 1);
	return (ret);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	int		printed_char_sum;
	size_t	i;
	va_list	ap;

	printed_char_sum = 0;
	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
			printed_char_sum += eval_format(fd, format[++i], &ap);
		else
			printed_char_sum += write(fd, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (printed_char_sum);
}
