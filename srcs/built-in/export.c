/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 02:30:14 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 12:21:35 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_print(void)
{
	t_envlist	*sorted_env;
	t_envlist	*ptr;

	sorted_env = env_list_sort(env_list_copy_all(g_data.env_list));
	ptr = sorted_env;
	while (ptr)
	{
		if (ptr->export && ptr->value)
			printf("declare -x %s=\"%s\"\n", ptr->name, ptr->value);
		else if (ptr->export)
			printf("declare -x %s\n", ptr->name);
		ptr = ptr->next;
	}
	free_env_list(&sorted_env);
}

static void	export_split_set(const char *arg)
{
	t_envlist	new_var;
	t_envlist	*found_env;

	new_var = split_env(arg);
	if (new_var.name)
	{
		ft_setenv(new_var.name, new_var.value, 1);
		found_env = ft_findenv(new_var.name);
		found_env->export = true;
	}
	free(new_var.name);
	free(new_var.value);
}

static void	export_change_status(char *arg)
{
	t_envlist	*found_env;

	found_env = ft_findenv(arg);
	if (found_env)
		found_env->export = true;
	else
	{
		ft_setenv(arg, NULL, 0);
		found_env = ft_findenv(arg);
		if (found_env)
			found_env->export = true;
	}
}

static void	export_new_var(char **argv)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 1 && ft_strchr(argv[i], '='))
			export_split_set(argv[i]);
		else
			export_change_status(argv[i]);
		i++;
	}
}

void	built_in_export(char **argv)
{
	if (!argv || !argv[0])
		exit_error("export");
	else if (!argv[1])
		export_print();
	else
		export_new_var(argv);
}
