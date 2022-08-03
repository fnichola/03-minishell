/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:19:10 by fnichola          #+#    #+#             */
/*   Updated: 2022/07/31 16:51:48 by akihito          ###   ########.fr       */
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

	ptr = malloc(size);
	if (!ptr)
		exit_error("malloc");
	return (ptr);
}

void	ft_perror(char *perror_str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(perror_str);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i] ||
			s1[i] == 0 || s2[i] == 0)
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

