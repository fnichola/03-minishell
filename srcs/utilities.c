/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:19:10 by fnichola          #+#    #+#             */
/*   Updated: 2022/04/06 14:37:06 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	*malloc_error_check(size_t size)
{
	void	*ptr;

	printf("malloc!\n");
	ptr = malloc(size);
	if (!ptr)
		exit_error("malloc");
	return (ptr);
}
