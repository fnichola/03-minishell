/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:19:10 by fnichola          #+#    #+#             */
/*   Updated: 2022/07/04 15:45:12 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_find_env(char *env_str, char **envp)
{
	int		envp_i;
	int		env_str_len;
	char	**ans_env;

	// printf("ft_find_env\n");
	envp_i = 0;
	env_str_len = ft_strlen(env_str);
	// printf("env_str_len %d\n", env_str_len);
	while (envp[envp_i])
	{
		printf("env_str %s\n", env_str);
		// printf("envp[envp_i] %s\n", envp[envp_i]);
		if (!ft_strncmp(env_str, envp[envp_i], env_str_len))
		{
			ans_env = ft_split(envp[envp_i], '=');
			return (ans_env[1]);
		}
		envp_i++;
	}
	return (NULL);
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

void	ft_perror(char *perror_str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(perror_str);
}

void	*malloc_error_check(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit_error("malloc");
	return (ptr);
}
