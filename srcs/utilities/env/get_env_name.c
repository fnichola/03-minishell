/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:07:07 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 05:36:57 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Extract name from an env string ("NAME=VALUE")
 * Allocates and returns a new string.
 */
char	*get_env_name(char *env)
{
	char	*value_env;
	int		name_len;
	char	*name;

	name_len = 0;
	value_env = ft_strchr(env, '=');
	name_len = value_env - env;
	name = (char *)malloc(sizeof(char) * (name_len + 1));
	ft_strncpy(name, env, name_len);
	return (name);
}
