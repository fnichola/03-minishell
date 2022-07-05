/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:23:49 by akihito           #+#    #+#             */
/*   Updated: 2022/07/03 13:57:25 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

void	built_in_echo(char **argv)//環境変数はまだ、echo ?$も無限ループしてしまう。
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
	if (argv[arg_i] && ft_strcmp(argv[arg_i], "-n") == 0 && arg_i++)//echo -n test とechoの直後しかオプションとして認識しない
	{
		option++;
	}
	if (option)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	while (argv[arg_i])
	{
		ft_putstr_fd(argv[arg_i], STDOUT_FILENO);
		if (argv[arg_i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		arg_i++;
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
	return ;
}

void	built_in_cd(char **argv)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	printf("old_pwd = %s\n", old_pwd);
	printf("%s\n", argv[1]);
	if (argv[1] && \
		argv[1][0] && \
		chdir(argv[1]) == -1)
	{
		ft_perror("cd");
		//エラーのステータス更新
		free(old_pwd);
		return ;
	}
	// argv
	return ;
}