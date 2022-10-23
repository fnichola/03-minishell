/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:57:21 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/21 13:02:53 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(char *str)
{
	char	*err_str;

	err_str = ft_strjoin("minishell: ", str);
	if (!err_str)
		perror("minishell: ");
	else
		perror(err_str);
	exit(EXIT_FAILURE);
}

void	error_command(char *str1, char *str2, char *str3)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	if (str2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(str2, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
	}
	if (str3)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str3, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	// if (error_command)
	// 	perror(error_command);
}
