/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_to_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 04:05:21 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 14:52:17 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_list_size(t_envlist	*ptr)
{
	size_t	i;

	i = 0;
	ptr = g_data.env_list;
	if (!ptr)
		return (-1);
	while (ptr)
	{
		if (ptr->export)
			i++;
		ptr = ptr->next;
	}
	return (i);
}

char	**export_to_envp(void)
{
	char		**new_envp;
	t_envlist	*ptr;
	char		*env_entry;
	char		*tmp_str;
	size_t		i;

	ptr = g_data.env_list;
	i = count_env_list_size(ptr);
	if (i < 0)
		return (NULL);
	new_envp = malloc_error_check(sizeof(char *) * (i + 1));
	ptr = g_data.env_list;
	i = 0;
	while (ptr)
	{
		tmp_str = ft_strjoin(ptr->name, "=");
		env_entry = ft_strjoin(tmp_str, ptr->value);
		free(tmp_str);
		new_envp[i++] = env_entry;
		ptr = ptr->next;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
