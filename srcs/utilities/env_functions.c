/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:27:20 by akihito           #+#    #+#             */
/*   Updated: 2022/08/29 07:37:17 by fnichola         ###   ########.fr       */
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

// t_envlist	*ft_set_env(t_envlist *env_list, char *name, char *value, int add)
// {
// 	char		*addValue;
// 	t_envlist	*tmp;

// 	tmp = env_list->next;
// 	addValue = "";
// 	// printf("set_env\n");
// 	// printf("value = %s\n", value);
// 	while (tmp != env_list)
// 	{
// 		if (!ft_str_match(tmp->name, name))
// 		{
// 			printf("tmp->name = %s\n", tmp->name);
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
// 			free(name);
// 			return (env_list);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (env_list);
// }

// void	put_env_asci_order(void)
// {
// 	t_envlist	*tmp;
// 	t_envlist	*put_tmp;

// 	put_tmp = NULL;
// 	tmp = g_data.env_list;
// 	while (tmp)
// 	{
// 		if (sorted == NULL || ft_strcmp(sorted->name, tmp->name) < 0)
// 		{
// 			if (put_tmp == NULL)
// 				put_tmp = tmp;
// 			else if (ft_strcmp(tmp->name, put_tmp->name) < 0)
// 				put_tmp = tmp;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (put_tmp)
// 	{
// 		if (put_tmp->value)
// 			printf("declare -x %s=\"%s\"\n", put_tmp->name, put_tmp->value);
// 		else
// 			printf("declare -x %s\n", put_tmp->name);
// 		put_env_asci_order(e_list, put_tmp);
// 	}
// 	return ;
// }


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
				tmp1 = ptr->prev;
				tmp2 = ptr->next->next;
				if (tmp1)
					tmp1->next = ptr->next;
				if (tmp2)
					tmp2->prev = ptr;
				ptr->next->prev = tmp1;
				ptr->next->next = ptr;
				ptr->prev = ptr->next;
				ptr->next = tmp2;
				is_sorted = false;
			}
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
