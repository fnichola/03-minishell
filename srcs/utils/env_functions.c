/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:27:20 by akihito           #+#    #+#             */
/*   Updated: 2022/08/03 13:54:39 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
/*
**	create, edit or search the list of environment variables.
*/

t_envlist	*init_env_list(char **envp)
{
	t_envlist	head;
	t_envlist	*now;
	size_t		i;

	i = 0;
	now = &head;
	if (envp[i] == NULL)
	{
		return (NULL);
	}
	while (envp[i])
	{
		now = create_env_list(envp[i], now);//ここでノードを作っていきリストを作る
		i++;
	}
	return (head.next);
}

t_envlist	*create_env_list(char *env, t_envlist *now)
{
	size_t		i;
	t_envlist	*node;

	node = (t_envlist *)malloc_error_check(sizeof(t_envlist));
	i = 0;
	node->key = get_env_key(env);
	node->value = get_env_value(env);
	now->next = node;
	node->next = NULL;
	return (node);
}

int	ft_strncpy(char *dest, char *src, size_t cpy_len)
{
	size_t	i;

	i = 0;
	if (cpy_len < 0 || !src)
	{
		exit_error("strncpy error\n");
		return (-1);
	}
	while (i < cpy_len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (0);
}

char	*get_env_key(char *env)
{
	// int		env_str_len;
	char	*value_env;
	int		find_index;
	int		key_len;
	char	*key_env;

	key_len = 0;
	find_index = 0;
	value_env = ft_strchr(env, '=');
	key_len = value_env - env;
	key_env = (char *)malloc(sizeof(char) * (key_len + 1));
	ft_strncpy(key_env, env, key_len);
	// printf("key_env = %s\n", key_env);
	// printf("key_len = %d\n", key_len);
	return (key_env);
}

char	*get_env_value(char *env)
{
	int		envp_i;
	int		env_str_len;
	char	*ans_env;

	envp_i = 0;
	env_str_len = ft_strlen(env);
	ans_env = ft_strchr(env, '=');
	(ans_env)++;//ここで　'='を消すERM_PROGRAM=vscodeでfind_indexが23になる
	return (ans_env);
}

char	*ft_getenv(t_envlist *elst, char *search_key)
{
	t_envlist	*tmp;

	printf("getenv\n");
	tmp = elst->next;
	while (elst)
	{
		if (ft_strcmp(elst->key, search_key) == 0)
			return (elst->value);
		elst = elst->next;
	}
	return (NULL);
}

t_envlist	*ft_set_env(t_envlist *env_list, char *key, char *value, int add)
{
	char		*addValue;
	t_envlist	*tmp;

	tmp = env_list->next;
	addValue = "";
	printf("set_env\n");
	printf("value = %s\n", value);
	while (tmp != env_list)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (value)
			{
				if (add)
					addValue = ft_wstrjoin(tmp->value, value);
				else
				{
					printf("ft_wstrdup\n");
					addValue = ft_wstrdup(value);
				}
				free(value);
				// free(env_list->value);
				env_list->value = addValue;
				printf("env_list->value %s\n", env_list->value);
			}
			free(key);
			return (env_list);
		}
		tmp = tmp->next;
	}
	return (env_list);
}
