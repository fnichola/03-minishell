/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:20:01 by fnichola          #+#    #+#             */
/*   Updated: 2021/10/24 22:00:30 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_print_str(char *s)
{
	int	ret;

	ret = 0;
	if (s)
		ret += write(1, s, ft_strlen(s));
	else
		ret += write(1, "(null)", 6);
	return (ret);
}

static int	eval_format(char conversion, va_list *ap)
{
	int		ret;

	ret = 0;
	if (conversion == 'c')
		ret += ft_print_char(va_arg(*ap, int));
	if (conversion == 's')
		ret += ft_print_str(va_arg(*ap, char *));
	if (conversion == 'p')
	{
		ret += write(1, "0x", 2);
		ret += ft_print_unum(va_arg(*ap, unsigned long), "0123456789abcdef", 0);
	}
	if (conversion == 'd' || conversion == 'i')
		ret += ft_print_num(va_arg(*ap, int));
	if (conversion == 'u')
		ret += ft_print_unum(va_arg(*ap, unsigned long), "0123456789", 1);
	if (conversion == 'x')
		ret += ft_print_unum(va_arg(*ap, unsigned long), "0123456789abcdef", 1);
	if (conversion == 'X')
		ret += ft_print_unum(va_arg(*ap, unsigned long), "0123456789ABCDEF", 1);
	if (conversion == '%')
		ret += write(1, "%", 1);
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	int		ret;
	size_t	i;
	va_list	ap;

	ret = 0;
	i = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
			ret += eval_format(format[++i], &ap);
		else
			ret += write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (ret);
}
