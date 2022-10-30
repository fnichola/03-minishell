/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex-utilities2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:21:55 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 15:24:06 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_delimeter(char c)
{
	if (!c
		|| c == ' '
		|| c == '\t'
		|| c == '|'
		|| c == '<'
		|| c == '>'
	)
		return (true);
	return (false);
}

bool	is_space(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (true);
	else
		return (false);
}
