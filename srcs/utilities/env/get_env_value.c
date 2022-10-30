/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:06:50 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 14:53:40 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Extract value from an env string ("NAME=VALUE")
 * Allocates and returns a new string.
 */
char	*get_env_value(char *env)
{
	char	*value;

	value = ft_strchr(env, '=');
	(value)++;
	return (ft_wstrdup(value));
}
