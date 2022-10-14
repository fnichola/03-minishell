/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:07:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 05:36:57 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Makes a new string in envp format ("NAME=VALUE").
 */
char	*env_to_string(const char *name, const char *value)
{
	char	*tmp_str;
	char	*env_string;

	if (!name)
		return (NULL);
	tmp_str = ft_strjoin(name, "=");
	env_string = ft_strjoin(tmp_str, value);
	free(tmp_str);
	return (env_string);
}
