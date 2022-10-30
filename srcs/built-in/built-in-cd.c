/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in-cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:42:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 11:42:57 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_cd(char **argv)
{
	char		*cwd;
	char		*now_pwd;
	char		*home_dir;

	cwd = getcwd(NULL, 0);
	home_dir = ft_getenv("HOME");
	if (argv[1] && argv[1][0] && chdir(argv[1]) == -1)
	{
		ft_perror("cd");
		free(cwd);
		return ;
	}
	else if (!argv[1] && chdir(home_dir) == -1)
	{
		ft_perror("cd");
		free(cwd);
		return ;
	}
	now_pwd = getcwd(NULL, 0);
	ft_setenv("PWD", now_pwd, 1);
	free(now_pwd);
	ft_setenv("OLDPWD", cwd, 1);
	free(cwd);
	g_data.exit_status = 0;
}
