/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:27:20 by akihito           #+#    #+#             */
/*   Updated: 2022/10/13 02:09:01 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_envlist **env_list)
{
	t_envlist	*ptr;
	t_envlist	*tmp;

	ptr = *env_list;
	while (ptr)
	{
		free(ptr->name);
		free(ptr->value);
		free(ptr->string);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	*env_list = NULL;
}

void	init_env_list(char **envp)
{
	size_t		i;
	char		*name;
	char		*value;
	t_envlist	*new_var;

	i = 0;
	while (envp[i])
	{
		name = get_env_name(envp[i]);
		value =	get_env_value(envp[i]);
		new_var = env_list_new(name, value, ft_strdup(envp[i]));
		env_list_add_back(&g_data.env_list, new_var);
		new_var->export = true;
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

	while (ptr && ptr->next)
		ptr = ptr->next;
	return (ptr);
}

/**
 * Make a new t_envlist node.
 * The node can be made with name and value strings or with a raw env string
 * ("NAME=VALUE").
 * 
 * For convenience it can be called in three different ways,
 * NULL parameters will be auto-generated:
 * new_env = env_list_new(name, value, NULL);
 * new_env = env_list_new(NULL, NULL, string);
 * new_env = env_list_new(name, value, string);
 */
t_envlist	*env_list_new(char *name, char *value, char *string)
{
	t_envlist	*new;

	new = malloc_error_check(sizeof(t_envlist));
	if (!name && !value && string)
	{
		name = get_env_name(string);
		value = get_env_value(string);
	}
	if (!string)
	{
		string = env_to_string(name, value);
	}
	if (!name)
	{
		free(new);
		return (NULL);
	}
	new->name = name;
	new->value = value;
	new->string = string;
	new->next = NULL;
	new->prev = NULL;
	new->export = false;
	return (new);
}

t_envlist	*env_list_add_back(t_envlist **env_list, t_envlist *new_node)
{
	t_envlist	*last_node;

	if (!*env_list)
		*env_list = new_node;
	else 
	{
		last_node = env_list_last(*env_list);
		new_node->prev = last_node;
		last_node->next = new_node;
	}
	return (new_node);
}

int	ft_strncpy(char *dest, char *src, size_t cpy_len)
{
	size_t	i;

	i = 0;
	if (!src)
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

/**
 * Add or update an env variable.
 * If a variable with "name" doesn't exist it will be created.
 * If "name" exists and overwrite != 0 its value will be udpated.
 * Returns -1 if there are invalid parameters.
 */
int	ft_setenv(const char *name, const char *value, int overwrite)
{
	t_envlist	*node;
	t_envlist	*new_node;


	node = ft_findenv(name);
	if (!name || !ft_strlen(name) || ft_strchr(name, '='))
	{
		debug_log("ft_setenv: error!\n");
		errno = EINVAL;
		return (-1);
	}
	else if (node && overwrite)
	{
		free(node->value);
		if (value)
			node->value = ft_wstrdup(value);
		free(node->string);
		node->string = env_to_string(name, value);
	}
	else if (!node)
	{
		if (value)
		{
			new_node = env_list_new(ft_wstrdup(name), ft_wstrdup(value), NULL);
			env_list_add_back(&g_data.env_list, new_node);
		}
		else
		{
			new_node = env_list_new(ft_wstrdup(name), NULL, NULL);
			env_list_add_back(&g_data.env_list, new_node);
		}
	}
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

size_t	env_list_size(t_envlist *node)
{
	size_t	size;

	size = 0;
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
}

t_envlist *env_list_dup(t_envlist *node)
{
	t_envlist	*new_node;
	char		*name;
	char		*value;
	char		*string;

	name = ft_wstrdup(node->name);
	value = ft_wstrdup(node->value);
	string = ft_wstrdup(node->string);
	new_node = env_list_new(name, value, string);
	new_node->export = node->export;
	return (new_node);
}

t_envlist *env_list_copy_all(t_envlist *node)
{
	t_envlist	*new_list;

	new_list = NULL;
	while (node)
	{
		env_list_add_back(&new_list, env_list_dup(node));
		node = node->next;
	}
	return (new_list);
}

t_envlist *env_list_sort(t_envlist *env_list)
{
	bool		is_sorted;
	t_envlist	*ptr;

	is_sorted = false;
	ptr = env_list;
	if (!ptr || !ptr->next)
		return (NULL);

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
	return (env_list_first(ptr));
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

void	free_envp(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
	free(envp);
}
