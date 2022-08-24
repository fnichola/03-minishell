/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_str_match.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:04:22 by fnichola          #+#    #+#             */
/*   Updated: 2022/08/23 15:08:33 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Compare two strings, return true if they're an exact match. Length and case-sensitive.
 */
bool	is_str_match(char *s1, char *s2)
{
	if (!ft_strcmp(s1, s2) && ft_strlen(s1) == ft_strlen(s2))
		return true;
	else
		return false;
}

