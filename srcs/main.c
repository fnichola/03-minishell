/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/02/26 21:15:14 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>


int	main(int argc, char **argv)
{
	char	*line;
	(void)argc;
	(void)argv;

	while (1)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		if (!ft_strncmp(line, "exit", ft_strlen(line)))
			break ;	
		printf("%s\n", line);
		free(line);
	}
	free(line);
	ft_printf("exit\n");
	// rl_clear_history(); // requires GNU Readline
	return (0);
}
