/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_to_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:05:21 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 05:36:57 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**export_to_envp(void)
{
	char		**new_envp;
	t_envlist	*ptr;
	size_t		size;
	char		*env_entry;
	char		*tmp_str;
	size_t		i;

	size = 1;
	ptr = g_data.env_list;
	if (!ptr)
		return (NULL);
	while (ptr)
	{
		if (ptr->export)
			size++;
		ptr = ptr->next;
	}
	new_envp = malloc_error_check(sizeof(char *) * (size + 1));
	ptr = g_data.env_list;
	i = 0;
	while (ptr)
	{
		if (ptr->export)
		{
			tmp_str = ft_strjoin(ptr->name, "=");
			env_entry = ft_strjoin(tmp_str, ptr->value);
			free(tmp_str);
			new_envp[i] = env_entry;
			i++;
		}
		ptr = ptr->next;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
