/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 01:57:05 by akihito           #+#    #+#             */
/*   Updated: 2022/10/17 14:19:23 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// this check needs to be fixed!
bool	is_valid_variable(char *variable)
{
	if (ft_isdigit(variable[0]))
		return (0);
	else
		return (1);
}
