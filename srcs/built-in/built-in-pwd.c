/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in-pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:43:00 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 11:43:33 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_pwd(char **argv)
{
	char	*path_name;

	(void)argv;
	path_name = getcwd(NULL, 0);
	if (!path_name)
		ft_perror("pwd");
	else
	{
		printf("%s\n", path_name);
		free(path_name);
	}
	g_data.exit_status = 0;
}
