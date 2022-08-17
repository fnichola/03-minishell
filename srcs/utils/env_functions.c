/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:27:20 by akihito           #+#    #+#             */
/*   Updated: 2022/08/17 11:23:27 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

char	*ft_findenv(t_envlist *elst, char *search_key)
{
	t_envlist	*tmp;
	// char 		*found_value;

	tmp = elst->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, search_key) == 0)
		{
			printf("tmp->value = %s\n", tmp->value);
			// found_value = ft_wstrdup(tmp->value);
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_envlist	*ft_set_env(t_envlist *env_list, char *key, char *value, int add)
{
	char		*addValue;
	t_envlist	*tmp;

	tmp = env_list->next;
	addValue = "";
	// printf("set_env\n");
	// printf("value = %s\n", value);
	while (tmp != env_list)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			printf("tmp->key = %s\n", tmp->key);
			if (value)
			{
				if (add)
					addValue = ft_wstrjoin(tmp->value, value);
				else
				{
					// printf("ft_wstrdup\n");
					addValue = ft_wstrdup(value);
				}
				free(value);
				// free(env_list->value);
				tmp->value = addValue;
				// printf("tmp->value %s\n", tmp->value);
			}
			free(key);
			return (env_list);
		}
		tmp = tmp->next;
	}
	return (env_list);
}

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
	ssize_t	i;

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

t_envlist	*to_setenv(t_envlist *e_list, char *src_str, size_t i)
{
	char	*key;
	char	*value;
	int		mode;

	if (src_str[i] == '+')
	{
		key = ft_wsubstr(src_str, 0, i);
		value = ft_wsubstr(src_str, i + 2, ft_strlen(src_str) - i - 2);
		mode = 1;
	}
	else if (src_str[i] == '=')
	{
		key = ft_wsubstr(src_str, 0, i);
		value = ft_wsubstr(src_str, i + 1, ft_strlen(src_str) - i - 1);
		mode = 0;
	}
	else
	{
		key = ft_wstrdup(src_str);
		value = NULL;
		mode = 0;
	}
	return (ft_set_env(e_list, key, value, mode));
}
