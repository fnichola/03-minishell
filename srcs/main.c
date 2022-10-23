/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/23 09:23:00 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

t_minishell_data	g_data;
bool				g_debug;

int	minishell(char **envp)
{
	int			status;
	char		*line;
	t_list		*tokens;

	init_env_list(envp);
	g_data.command_table = NULL;
	init_built_in_table();
	status = 0;
	while (!status)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		tokens = tokenizer(line);
		if (tokens)
			parser(tokens);
		free(line);
		status = execute_commands();//ここでパイプ生成
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	g_debug = true;
	if (argc == 1)
	{
		debug_log("Starting Minishell\n");
		minishell(envp);
	}
	else
	{
		printf("error\n");
	}
	return (0);
}
