/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:23:49 by akihito           #+#    #+#             */
/*   Updated: 2022/08/09 00:33:11 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

void	built_in_echo(char **argv, t_envlist *e_list)//環境変数はまだ、echo ?$も無限ループしてしまう。
{
	int		option;
	size_t	arg_i;

	if (write(STDOUT_FILENO, NULL, 0) == -1)
	{
		ft_perror("echo: write error");
		exit(1);
	}
	option = 0;
	arg_i = 1;
	(void)e_list;
	if (argv[arg_i] && ft_strcmp(argv[arg_i], "-n") == 0 && arg_i++)//echo -n test とechoの直後しかオプションとして認識しない
	{
		option++;
	}
	while (argv[arg_i])
	{
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

void	built_in_cd(char **argv, t_envlist *e_list)
{
	char		*old_pwd;
	char		*now_pwd;
	t_envlist	*tmp;
	char		*home_dir;

	tmp = NULL;
	old_pwd = getcwd(NULL, 0);
	home_dir = ft_findenv(e_list, "HOME");
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
	if (ft_findenv(e_list, "PWD"))
		tmp = ft_set_env(e_list, ft_wstrdup("PWD"), getcwd(NULL, 0), 0);
	return ;
}

void	built_in_pwd(void)
{
	char	*path_name;

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

void	built_in_export(char **argv, t_envlist *e_list)
{//ascii順に並べる
	ssize_t		split_index;
	ssize_t		arg_i;
	t_envlist	*tmp;

	arg_i = 1;
	if (argv[arg_i] == NULL)
		put_env_asci_order(e_list, NULL);
	else//環境変数の追加または変更の処理
	{
		while (argv[arg_i])
		{
			split_index = check_shell_val(argv[arg_i]);
			if (split_index != -1)
			{
				printf("to_setenv\n");
				e_list = to_setenv(e_list, argv[arg_i], split_index);
			}
			else//エラー文　bash: export: `TEST++': not a valid identifier
				ft_puterror("export", argv[arg_i], "not a valid identifier");
			arg_i++;
		}
	}
	tmp = e_list->next;
	while (tmp)
	{
		printf("%s : %s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return ;
}

void	built_in_env(t_envlist	*e_list)
{
	t_envlist	*per_env;

	per_env = e_list;
	while (per_env)
	{
		if (per_env->value)
			printf("%s=%s\n", per_env->key, per_env->value);
		per_env = per_env->next;
	}
}
