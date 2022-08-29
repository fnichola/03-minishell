/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:27:20 by akihito           #+#    #+#             */
/*   Updated: 2022/08/29 03:33:38 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
**	create, edit or search the list of environment variables.
*/

void	free_env_list(void)
{
	t_envlist	*envp;
	t_envlist	*tmp;

	envp = g_data.env_list;
	while (envp)
	{
		free(envp->key);
		free(envp->value);
		tmp = envp;
		envp = envp->next;
		free(tmp);
	}
	g_data.env_list = NULL;
}

void	init_env_list(char **envp)
{
	size_t		i;
	char	*name;
	char	*value;

	i = 0;
	while (envp[i])
	{
		name = get_env_key(envp[i]);
		value =	get_env_value(envp[i]);
		env_list_add_back(name, value);
		i++;
	}
}

t_envlist	*env_list_last(void)
{
	t_envlist	*tmp;

	tmp = g_data.env_list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_envlist	*env_list_new(char *name, char *value)
{
	t_envlist	*new;

	new = malloc_error_check(sizeof(t_envlist));
	new->key = name;
	new->value = value;
	new->next = NULL;
}

void	*env_list_add_back(char *name, char *value)
{
	if (!g_data.env_list)
		g_data.env_list = env_list_new(name, value);
	else 
		env_list_last()->next = env_list_new(name, value);
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
	return (ft_wstrdup(ans_env));
}

/**
 * Find an env variable and return a pointer to it's node.
 * Use ft_getenv to retrieve the value directly.
 */
t_envlist	*ft_findenv(const char *name)
{
	t_envlist	*tmp;

	tmp = g_data.env_list;
	while (tmp)
	{
		if (is_str_match(tmp->key, name))
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * Find an env variable and return a pointer to it's VALUE.
 * Returns NULL if not found.
 */
char	*ft_getenv(char *name)
{
	t_envlist	*tmp;

	tmp = g_data.env_list;
	while (tmp)
	{
		if (is_str_match(tmp->key, name))
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	t_envlist	*node;

	printf("ft_setenv: name = %s, value = %s\n", name, value);

	node = ft_findenv(name);
	if (!name || !ft_strlen(name) || ft_strchr(name, '='))
	{
		printf("ft_setenv: error!\n");
		errno = EINVAL;
		return (-1);
	}
	else if (node && overwrite)
	{
		free(node->value);
		node->value = ft_wstrdup(value);
	}
	else if (!node);
		env_list_add_back(ft_wstrdup(name), ft_wstrdup(value));
	return (0);
}

// t_envlist	*ft_set_env(t_envlist *env_list, char *key, char *value, int add)
// {
// 	char		*addValue;
// 	t_envlist	*tmp;

// 	tmp = env_list->next;
// 	addValue = "";
// 	// printf("set_env\n");
// 	// printf("value = %s\n", value);
// 	while (tmp != env_list)
// 	{
// 		if (!ft_str_match(tmp->key, key))
// 		{
// 			printf("tmp->key = %s\n", tmp->key);
// 			if (value)
// 			{
// 				if (add)
// 					addValue = ft_wstrjoin(tmp->value, value);
// 				else
// 				{
// 					// printf("ft_wstrdup\n");
// 					addValue = ft_wstrdup(value);
// 				}
// 				free(value);
// 				// free(env_list->value);
// 				tmp->value = addValue;
// 				// printf("tmp->value %s\n", tmp->value);
// 			}
// 			free(key);
// 			return (env_list);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (env_list);
// }

void	put_env_asci_order(t_envlist *e_list, t_envlist *sorted)
{
	t_envlist	*tmp;
	t_envlist	*put_tmp;

	put_tmp = NULL;
	tmp = e_list;
	while (tmp)
	{
		if (sorted == NULL || ft_strcmp(sorted->key, tmp->key) < 0)
		{
			if (put_tmp == NULL)
				put_tmp = tmp;
			else if (ft_strcmp(tmp->key, put_tmp->key) < 0)
				put_tmp = tmp;
		}
		tmp = tmp->next;
	}
	if (put_tmp)
	{
		if (put_tmp->value)
			printf("declare -x %s=\"%s\"\n", put_tmp->key, put_tmp->value);
		else
			printf("declare -x %s\n", put_tmp->key);
		put_env_asci_order(e_list, put_tmp);
	}
	return ;
}

int	check_shell_val(char *src_str)
{
	size_t	i;

	i = 0;
	while (src_str[i])
	{// = か　+があったらそのインデックスを返す　+はその後に追加する // export += "test"は後ろに追加する //指定の文字以外が入っていたらエラー
		if (0 < i && \
			((src_str[i] == '+' && src_str[i + 1] == '=') || \
			src_str[i] == '='))
			break ;
		if (!(src_str[i] == '_' || \
			ft_isalnum(src_str[i])) || \
			ft_isdigit(src_str[0]))
			return (-1);
		i++;
	}
	return (i);
}

void	to_setenv(t_envlist *e_list, char *src_str, size_t i)
{
	char	*key;
	char	*value;

	if (src_str[i] == '+')
	{
		key = ft_wsubstr(src_str, 0, i);
		value = ft_wsubstr(src_str, i + 2, ft_strlen(src_str) - i - 2);
		value = ft_strjoin(ft_getenv(key), value);
	}
	else if (src_str[i] == '=')
	{
		key = ft_wsubstr(src_str, 0, i);
		value = ft_wsubstr(src_str, i + 1, ft_strlen(src_str) - i - 1);
	}
	else
	{
		key = ft_wstrdup(src_str);
		value = NULL;
	}
	ft_setenv(key, value, 1);
}
