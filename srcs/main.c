/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/08/24 12:00:14 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

int	minishell(char **envp)
{
	int			status;
	char		*line;
	t_list		*tokens;

	g_data.env_list = init_env_list(envp);
	g_data.command_table = NULL;
	init_built_in_table();
	status = 0;
	printf("minishell\n");
	while (!status)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		tokens = tokenizer(line);
		// printf("tokens %s\n", (char *)tokens->next->content);
		g_data.command_table = parser(tokens, g_data.env_list);
		// printf("g_data.command_table %s\n", (char *)g_data.command_table->content->);
		free(line);
		printf("before execute\n");
			status = execute_commands(envp);
		ft_lstclear(&g_data.command_table, free_command_table);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc == 1)
	{
		minishell(envp);
	}
	else
	{
		ft_printf("error\n");
	}
	return (0);
}
