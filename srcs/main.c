/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 16:47:26 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "get_next_line.h"

t_minishell_data	g_data;

int	event(void)
{
	return (0);
}

int	wget_next_line(int script_fd, char **line)
{
	*line = get_next_line(script_fd);
	if (!*line)
		*line = ft_wstrdup("exit");
	if (*line)
		*line[ft_strlen(*line) - 1] = 0;
	else
		return (-1);
	return (0);
}

int	minishell(char **envp)
{
	char		*line;
	t_list		*tokens;

	inits(envp);
	rl_event_hook = event;
	while (1)
	{
		rl_outstream = stderr;
		line = readline("minishell$ ");
		if (!line)
			line = ft_wstrdup("exit");
		if (line && *line)
			add_history(line);
		tokens = tokenizer(line);
		if (tokens)
			parser(tokens);
		free(line);
		execute_commands();
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	ft_wsignal(SIGINT, signal_handler);
	ft_wsignal(SIGQUIT, SIG_IGN);
	if (argc == 1)
		minishell(envp);
	else
		ft_perror("Error");
	return (0);
}
