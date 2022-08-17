/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:47:07 by akihito           #+#    #+#             */
/*   Updated: 2022/08/17 11:23:31 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_wstrjoin(char *str1, char *str2)
{
	char	*joined_str;

	joined_str = ft_strjoin(str1, str2);
	if (!joined_str)
		exit_error("malloc");
	return (joined_str);
}

char	*ft_wstrdup(const char *src)
{
	char	*res;

	res = ft_strdup(src);
	if (res == NULL)
		exit_error("malloc");
	return (res);
}

char	*ft_wsubstr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	ret = ft_substr(s, start, len);
	if (ret == NULL)
	{
		ft_perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

int	ft_wpipe(int fd[2])
{
	int	status;

	status = pipe(fd);
	if (status == -1)
	{
		ft_perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (status);
}
