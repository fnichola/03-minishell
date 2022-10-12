/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 06:24:10 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/12 09:07:02 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "minishell.h"

void	debug_log(const char *format, ...)
{
	if (!g_debug)
		return ;
	va_list args;
	va_start(args, format);
	printf("\033[0;33m");
	vprintf(format, args);
	printf("\033[0m");
	fflush(stdout);
	va_end(args);
}
