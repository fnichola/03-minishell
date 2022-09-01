/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:27:20 by akihito           #+#    #+#             */
/*   Updated: 2022/09/01 01:56:29 by fnichola         ###   ########.fr       */
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
		free(envp->name);
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
		ft_findenv(name)->export = true;
		i++;
	}
}

t_envlist	*env_list_first(t_envlist *ptr)
{
	while (ptr && ptr->prev)
		ptr = ptr->prev;
	return (ptr);
}

t_envlist	*env_list_last(t_envlist *ptr)
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
	new->name = name;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	new->export = false;
}

void	*env_list_add_back(char *name, char *value)
{
	t_envlist	*new_var;
	t_envlist	*last_var;

	new_var = env_list_new(name, value);
	if (!g_data.env_list)
		g_data.env_list = new_var;
	else 
	{
		last_var = env_list_last(g_data.env_list);
		new_var->prev = last_var;
		last_var->next = new_var;
	}
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
		if (is_str_match(tmp->name, name))
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
		if (is_str_match(tmp->name, name))
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

void	env_list_swap_next(t_envlist *node)
{
	t_envlist	*tmp1;
	t_envlist	*tmp2;

	tmp1 = node->prev;
	tmp2 = node->next->next;
	if (tmp1)
		tmp1->next = node->next;
	if (tmp2)
		tmp2->prev = node;
	node->next->prev = tmp1;
	node->next->next = node;
	node->prev = node->next;
	node->next = tmp2;
}

void	env_list_sort(void)
{
	bool		is_sorted;
	t_envlist	*ptr;
	t_envlist	*tmp1;
	t_envlist	*tmp2;

	is_sorted = false;
	ptr = g_data.env_list;
	if (!ptr || !ptr->next)
		return ;

	while(!is_sorted)
	{
		is_sorted = true;
		ptr = env_list_first(ptr);
		while (ptr && ptr->next)
		{
			if (ft_strcmp(ptr->name, ptr->next->name) > 0)
			{
				env_list_swap_next(ptr);
				is_sorted = false;
			}
			if (ptr->next)
				ptr = ptr->next;
		}
	}
	g_data.env_list = env_list_first(ptr);
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
	char	*name;
	char	*value;

	if (src_str[i] == '+')
	{
		name = ft_wsubstr(src_str, 0, i);
		value = ft_wsubstr(src_str, i + 2, ft_strlen(src_str) - i - 2);
		value = ft_strjoin(ft_getenv(name), value);
	}
	else if (src_str[i] == '=')
	{
		name = ft_wsubstr(src_str, 0, i);
		value = ft_wsubstr(src_str, i + 1, ft_strlen(src_str) - i - 1);
	}
	else
	{
		name = ft_wstrdup(src_str);
		value = NULL;
	}
	ft_setenv(name, value, 1);
}
