/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:57:21 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 14:37:28 by atomizaw         ###   ########.fr       */
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
