/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:23:49 by akihito           #+#    #+#             */
/*   Updated: 2022/08/24 11:54:35 by fnichola         ###   ########.fr       */
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
	};
	t_str_func_table	*built_ins;

	built_ins = malloc_error_check(sizeof(temp));
	g_data.num_built_ins = sizeof(temp) / sizeof(t_str_func_table);
	printf("num_built_ins = %d\n", g_data.num_built_ins);
	ft_memcpy(built_ins, temp, sizeof(temp));
	g_data.built_ins = built_ins;
}

void	built_in_echo(char **argv)//環境変数はまだ、echo ?$も無限ループしてしまう。
{
	int		option;
	size_t	arg_i;
	// char	*put_str;

	if (write(STDOUT_FILENO, NULL, 0) == -1)
	{
		ft_perror("echo: write error");
		exit(1);
	}
	option = 0;
	arg_i = 1;
	if (argv[arg_i] && ft_strcmp(argv[arg_i], "-n") == 0 && arg_i++)//echo -n test とechoの直後しかオプションとして認識しない
	{
		option++;
	}
	while (argv[arg_i])
	{
		// printf("while\n");
		// put_str = ft_echo_env(argv[arg_i], e_list);//echoで文字列中にシェル変数があったら、そのシェル変数を展開してあげた文字列を返してあげる。
		// printf("arg_i = %zu\n", arg_i);
		ft_putstr_fd(argv[arg_i], STDOUT_FILENO);
		if (argv[arg_i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		arg_i++;
	}
	if (!option)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return ;
}

void	built_in_cd(char **argv)
{
	char		*old_pwd;
	char		*now_pwd;
	t_envlist	*tmp;
	char		*home_dir;

	tmp = NULL;
	old_pwd = getcwd(NULL, 0);
	home_dir = ft_findenv(g_data.env_list, "HOME");
	if (argv[1] && argv[1][0] && chdir(argv[1]) == -1)
	{//status=1
		ft_perror("cd");//エラーのステータス更新
		free(old_pwd);
		return ;
	}
	else if (!argv[1] && chdir(home_dir) == -1)//cdの引数がなかったら、環境変数HOMEのディレクトリに移動する
	{//status=0
		ft_perror("cd");
		free(old_pwd);
		return ;
	}
	now_pwd = getcwd(NULL, 0);
	if (ft_findenv(g_data.env_list, "PWD"))
		tmp = ft_set_env(g_data.env_list, ft_wstrdup("PWD"), getcwd(NULL, 0), 0);
	return ;
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
	}
	// return (path_name);
	return ;
}

void	built_in_export(char **argv)
{//ascii順に並べる
	ssize_t		split_index;
	ssize_t		arg_i;
	t_envlist	*tmp;

	arg_i = 1;
	if (argv[arg_i] == NULL)
		put_env_asci_order(g_data.env_list, NULL);
	else//環境変数の追加または変更の処理
	{
		while (argv[arg_i])
		{
			split_index = check_shell_val(argv[arg_i]);
			if (split_index != -1)
			{
				printf("to_setenv\n");
				g_data.env_list = to_setenv(g_data.env_list, argv[arg_i], split_index);
			}
			else//エラー文　bash: export: `TEST++': not a valid identifier
				ft_puterror("export", argv[arg_i], "not a valid identifier");
			arg_i++;
		}
	}
	tmp = g_data.env_list->next;
	while (tmp)
	{
		printf("%s : %s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
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
			printf("%s=%s\n", per_env->key, per_env->value);
		per_env = per_env->next;
	}
}