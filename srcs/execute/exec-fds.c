/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec-fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:58:36 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 14:27:48 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_exec_fds(void)
{
	t_command	*ct;

	ct = g_data.command_table;
	while (ct)
	{
		if (ct->input_fd != STDIN_FILENO)
			close(ct->input_fd);
		if (ct->output_fd != STDOUT_FILENO)
			close(ct->output_fd);
		ct = ct->next;
	}
}

void	heredoc_add_line(t_command *cmd, char *line)
{
	static size_t	size = 8;
	size_t			i;
	size_t			j;
	char			**new_heredoc;

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
		new_heredoc = malloc_error_check(sizeof(char *) * size);
		j = 0;
		while (j < i)
		{
			new_heredoc[j] = cmd->heredoc[j];
			j++;
		}
		free (cmd->heredoc);
		cmd->heredoc = new_heredoc;
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
	size_front = env_len + start; // size of before + var_name
	size_back = ft_strlen(*line + end); // size after var_name
	new_str = malloc_error_check(sizeof(char) * (size_front + size_back));
	ft_strlcpy(new_str, *line, start);
	if (env)
		ft_strlcat(new_str, env, size_front);
	ft_strlcat(new_str, *line + end, size_front + size_back);
	free(*line);
	*line = new_str;
}

void	heredoc_expand_variables(char **line)
{
	size_t	i;
	size_t	j;
	char 	*var_name;
	char	*found_env;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && ft_isalpha((*line)[i + 1]))
		{
			j = ++i;
			while (ft_isalnum((*line)[j]))
				j++;
			var_name = ft_substr((*line), i, (j - i));
			found_env = ft_getenv(var_name);
			heredoc_insert_env(line, found_env, i, j);
			if (found_env)
				i += ft_strlen(found_env) - 1;
			else
				i--;
			free(var_name);
		}
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

static int	update_input_redirect(t_redirect *r, t_command *cmd)
{
	int		fd;
	char	*line;
	int		pipe_fd[2];
	int		i;

	if (r->append)
	{
		pipe(pipe_fd);
		if (cmd->input_fd != STDIN_FILENO)
			close(cmd->input_fd);
		cmd->input_fd = pipe_fd[0];
		g_data.sig_int = false;
		while (!g_data.sig_int)
		{
			line = readline("> ");
			if (!line)
				break ;
			else if (g_data.sig_int || is_str_match(line, r->filename))
			{
				free(line);
				break ;
			}
			heredoc_expand_variables(&line);
			heredoc_add_line(cmd, line);
		}
		rl_set_signals();

		i = 0;
		while(!g_data.sig_int && cmd->heredoc && cmd->heredoc[i])
		{
			write(pipe_fd[1], cmd->heredoc[i], ft_strlen(cmd->heredoc[i]));
			write(pipe_fd[1], "\n", 1);
			i++;
		}
		close(pipe_fd[1]);
		return (cmd->input_fd);
	}
	else
	{
		fd = open(r->filename, O_RDONLY);
		if (fd >= 0)
		{
			if (cmd->input_fd != STDIN_FILENO)
				close(cmd->input_fd);
			cmd->input_fd = fd;
		}
		return (fd);
	}
}

static int	update_output_redirect(t_redirect *r, t_command *cmd)
{
	int	fd;

	fd = open(r->filename, O_WRONLY | O_CREAT | !r->append * O_TRUNC | r->append * O_APPEND, 0666);
	if (fd >= 0)
	{
		if (cmd->output_fd != STDOUT_FILENO)
			close(cmd->output_fd);
		cmd->output_fd = fd;
	}
	return (fd);
}

int	process_redirect_list(t_command *cmd)
{
	t_redirect	*r;
	int			fd;

	r = cmd->redirects;
	fd = 0;
	while (r)
	{
		if (r->type == INPUT_REDIRECT)
			fd = update_input_redirect(r, cmd);
		else if (r->type == OUTPUT_REDIRECT)
			fd = update_output_redirect(r, cmd);
		if (fd < 0)
		{
			ft_perror(r->filename);
			break ;
		}
		r = r->next;
	}
	return (fd);
}

static void	connect_redirects(void)
{
	t_command	*ct;

	ct = g_data.command_table;
	while (ct)
	{
		if (process_redirect_list(ct) < 0)
			ct = del_command(ct);
		else
			ct = ct->next;
	}
}

static void	connect_pipes(void)
{
	int			pipe_fd[2];
	t_command	*ct;

	ct = g_data.command_table;
	ct->input_fd = STDIN_FILENO;
	while (ct->next)
	{
		ft_wpipe(pipe_fd);
		ct->output_fd = pipe_fd[1];
		ct->next->input_fd = pipe_fd[0];
		ct = ct->next;
	}
	ct->output_fd = STDOUT_FILENO;
}

void	prepare_exec_fds(void)
{
	connect_pipes();
	connect_redirects();
	int i = 0;
	for (t_command *ct = g_data.command_table; ct; ct = ct->next)
	{
		i++;
	}
}
