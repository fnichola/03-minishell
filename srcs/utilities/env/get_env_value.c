/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:06:50 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 05:36:57 by fnichola         ###   ########.fr       */
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
	(value)++;//ここで　'='を消すERM_PROGRAM=vscodeでfind_indexが23になる
	return (ft_wstrdup(value));
}
