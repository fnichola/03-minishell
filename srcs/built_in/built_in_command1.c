/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:23:49 by akihito           #+#    #+#             */
/*   Updated: 2022/10/28 19:00:24 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

void	init_built_in_table(void)
{
	const t_str_func_table	temp[] = {
		{"echo",	&built_in_echo},
		{"cd",		&built_in_cd},
		{"pwd",		&built_in_pwd},
		{"env",		&built_in_env},
		{"export",	&built_in_export},
		{"exit",	&built_in_exit},
		{"unset",   &built_in_unset},
	};
	t_str_func_table	*built_ins;

	built_ins = malloc_error_check(sizeof(temp));
	g_data.num_built_ins = sizeof(temp) / sizeof(t_str_func_table);
	ft_memcpy(built_ins, temp, sizeof(temp));
	g_data.built_ins = built_ins;
	g_data.exit_status = 0;
}

void	built_in_echo(char **argv)//環境変数はまだ、echo ?$も無限ループしてしまう。
{
	int		option;
	size_t	arg_i;

	debug_log("built_in_echo\n");
	if (write(STDOUT_FILENO, NULL, 0) == -1)
	{
		ft_perror("echo: write error");
		exit(1);
	}
	option = 0;
	arg_i = 0;
	if (argv[arg_i] && ft_strcmp(argv[arg_i], "-n") == 0 && arg_i++)//echo -n test とechoの直後しかオプションとして認識しない
		option++;
	while (argv[++arg_i])
	{
		if (!ft_strcmp(argv[arg_i], "$?"))
			ft_putstr_fd(ft_itoa(g_data.exit_status), STDOUT_FILENO);
		else
			ft_putstr_fd(argv[arg_i], STDOUT_FILENO);
		if (argv[arg_i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	debug_log("built_in_echo g_data.exit_status %d\n", g_data.exit_status);
	if (!option)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return ;
}

void	built_in_cd(char **argv)
{
	char		*cwd;
	char		*now_pwd;
	char		*home_dir;
	// char		*old_pwd;

	cwd = getcwd(NULL, 0);
	home_dir = ft_getenv("HOME");
	if (argv[1] && argv[1][0] && chdir(argv[1]) == -1)
	{//status=1
		ft_perror("cd");//エラーのステータス更新
		free(cwd);
		return ;
	}
	else if (!argv[1] && chdir(home_dir) == -1)//cdの引数がなかったら、環境変数HOMEのディレクトリに移動する
	{//status=0
		ft_perror("cd");
		free(cwd);
		return ;
	}
	// else if (argv[1] && argv[1] == '-')
	// {
	// 	old_pwd = ft_getenv("OLDPWD");
	// 	if (old_pwd)
	// 	{
	// 		if (chdir(old_pwd) == -1);
	// 		{
	// 			ft_perror("cd");
	// 			free(cwd);
	// 			return ;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		ft_puterror("cd", "OLDPWD not set", NULL);
	// 		free(cwd);
	// 		return ;
	// 	}
	// }
	now_pwd = getcwd(NULL, 0);
	ft_setenv("PWD", now_pwd, 1);
	free(now_pwd);
	ft_setenv("OLDPWD", cwd, 1);
	free(cwd);
}

void	built_in_pwd(char **argv)
{
	char	*path_name;

	(void)argv;
	if (write(STDOUT_FILENO, NULL, 0) == -1)//標準出力エラー
	{//エラー
		exit_error("pwd: write error");
	}
	path_name = getcwd(NULL, 0);
	if (!path_name)
	{//エラー
		exit_error("pwd");
	}
	else
	{//正常
		printf("%s\n", path_name);
		free(path_name);
	}
	// return (path_name);
	return ;
}

void	built_in_env(char **argv)
{
	t_envlist	*per_env;

	(void)argv;
	per_env = g_data.env_list;
	while (per_env)
	{
		if (per_env->value)
			printf("%s=%s\n", per_env->name, per_env->value);
		per_env = per_env->next;
	}
}
