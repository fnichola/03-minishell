/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/29 13:10:31 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "get_next_line.h"


t_minishell_data	g_data;
bool				g_debug;

int	minishell(char **envp, int script_fd)
{
	int			status;
	char		*line;
	t_list		*tokens;

	init_env_list(envp);
	g_data.command_table = NULL;
	g_data.is_piped = 0;
	init_built_in_table();
	status = 0;
	while (!status)
	{
		g_data.is_piped = 0;
		if (script_fd >= 0)
		{
			line = get_next_line(script_fd);
			if (!line)
				line = ft_wstrdup("exit");
			if (line)
				line[ft_strlen(line) - 1] = 0;
			else
				break ;
		}
		else
		{
			line = readline("minishell$ ");
			if (!line)
				line = ft_wstrdup("exit");
			if (line && *line)
				add_history(line);
		}
		tokens = tokenizer(line);
		if (tokens)
			parser(tokens);
		free(line);
		status = execute_commands();//ここでパイプ生成
		debug_log("g_data.exit_status %d\n", g_data.exit_status);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;

	ft_wsignal(SIGINT, signal_handler);// ctrlC
	ft_wsignal(SIGQUIT, SIG_IGN);// ctrl 
	int	fd;
	// g_debug = true;
	if (argc == 1)
	{
		debug_log("Starting Minishell\n");
		minishell(envp, -1);
	}
	else if (argc == 2 && !access(argv[1], X_OK))
	{
		fd = open(argv[1], O_RDONLY);
		if (fd >= 0)
			minishell(envp, fd);
		else
			ft_perror(argv[1]);
	}
	else
	{
		ft_perror("Error");
	}
	return (0);
}
