/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:39:42 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 14:49:55 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	realloc_heredoc(t_command *cmd, size_t new_size)
{
	char	**new_heredoc;
	size_t	j;

	new_heredoc = malloc_error_check(sizeof(char *) * new_size);
	j = 0;
	while (cmd->heredoc[j])
	{
		new_heredoc[j] = cmd->heredoc[j];
		j++;
	}
	free (cmd->heredoc);
	cmd->heredoc = new_heredoc;
}

void	heredoc_add_line(t_command *cmd, char *line)
{
	static size_t	size = 32;
	size_t			i;

	if (!cmd->heredoc)
	{
		cmd->heredoc = malloc_error_check(sizeof(char *) * size);
		cmd->heredoc[0] = NULL;
	}
	i = 0;
	while (cmd->heredoc[i])
		i++;
	if (i >= size - 1)
	{
		size *= 2;
		realloc_heredoc(cmd, size);
	}
	cmd->heredoc[i] = line;
	cmd->heredoc[i + 1] = NULL;
}

/*
 * Inserts a found env variable value in the middle of a string.
 * 'start' points to the first char of var name, after the '$'.
 * 'end' points to the character after the variable name.
 * The new combined string is returned in *line, old *line is freed.
 */
void	heredoc_insert_env(char **line, char *env, size_t start, size_t end)
{
	size_t	size_front;
	size_t	size_back;
	size_t	env_len;
	char	*new_str;

	env_len = 0;
	if (env)
		env_len = ft_strlen(env);
	size_front = env_len + start;
	size_back = ft_strlen(*line + end);
	new_str = malloc_error_check(sizeof(char) * (size_front + size_back));
	ft_strlcpy(new_str, *line, start);
	if (env)
		ft_strlcat(new_str, env, size_front);
	ft_strlcat(new_str, *line + end, size_front + size_back);
	free(*line);
	*line = new_str;
}

void	heredoc_normal_var(char **line, size_t *i, size_t *j)
{
	char	*var_name;
	char	*found_env;

	*j = ++(*i);
	while (ft_isalnum((*line)[*j]))
		(*j)++;
	var_name = ft_substr((*line), *i, (*j - *i));
	found_env = ft_getenv(var_name);
	heredoc_insert_env(line, found_env, *i, *j);
	if (found_env)
		*i += ft_strlen(found_env) - 1;
	else
		(*i)--;
	free(var_name);
}

void	heredoc_expand_variables(char **line)
{
	size_t	i;
	size_t	j;
	char	*found_env;

	i = 0;
	j = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && ft_isalpha((*line)[i + 1]))
			heredoc_normal_var(line, &i, &j);
		else if ((*line)[i] == '$' && (*line)[i + 1] == '?')
		{
			found_env = ft_itoa(g_data.exit_status);
			heredoc_insert_env(line, found_env, i + 1, i + 2);
			free(found_env);
		}
		else
			i++;
	}
}
