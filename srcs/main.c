/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/02/28 21:16:26 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char	**parse_command(char *line)
{

}

int	main(int argc, char **argv)
{
	char	*line;
	char	**args;
	int		status;

	(void)argc;
	(void)argv;

	// initialize_minishell();
	status = 1;
	while (status)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		args = parse_command(line);
		// status = execute_command();
		if (!ft_strncmp(line, "exit", ft_strlen(line)))
			break ;	
		free(line);
	}
	free(line);
	ft_printf("exit\n");
	// rl_clear_history(); // requires GNU Readline
	return (0);
}
