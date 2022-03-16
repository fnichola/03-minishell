/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:39:20 by fnichola          #+#    #+#             */
/*   Updated: 2022/03/15 23:44:49 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_type	get_token(char *line)
{
	// t_state	state;
	size_t	i;
	char	**token;

	token = ft_split(line, ' ');
	i = 0;
	while (token[i] != NULL)
	{
		printf("token[i] = %s\n", token[i]);
		i++;
	}
	// i = 0;
	// state = NEUTRAL;
	// while (state == NEUTRAL && line[i])
	// {
	// 	if (line[i] == '|')
	// 		return T_BAR;
	// 	else if (line[i] == '$')
	// 		return T_DOLLAR;
	// 	else if (line[i] == '\n')
	// 		return T_NL;
	// 	else if (line[i] == '>')
	// 	{
	// 		state = GTGT;
	// 		i++;
	// 		break ;
	// 	}
	// 	else if (line[i] == '<')
	// 	{
	// 		state = LTLT;
	// 		i++;
	// 		break ;
	// 	}
	// 	else
	// 	{
	// 		state = IN_WORD;
	// 		continue ;
	// 	}
	// 	i++;
	// }
	// while (state == GTGT && line[i])
	// {
	// 	if (line[i] == '>')
	// 		return T_GTGT;
	// 	return T_GT;
	// }
	// while (state == LTLT && line[i])
	// {
	// 	if (line[i] == '<')
	// 		return T_LTLT;
	// 	return T_LT;
	// }
	// while (state == IN_SINGLE_QUOTE && line[i])
	// {
	// 	if (line[i] == '\'')
	// 		return T_WORD;
	// 	i++;
	// }
	// while (state == IN_DOUBLE_QUOTE && line[i])
	// {
	// 	if (line[i] == '"')
	// 		return T_WORD;
	// 	i++;
	// }
	// while (state == IN_WORD && line[i])
	// {
	// 	if (line[i] == '|' ||
	// 		line[i] == '<' ||
	// 		line[i] == '>' ||
	// 		line[i] == '\n' ||
	// 		line[i] == ' ' ||
	// 		line[i] == '\t')
	// 		return T_WORD;
	// 	i++;
	// }
	return T_EOF;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		i;
	(void)argc;
	(void)argv;
	i = 0;
	while (envp[i++] != NULL)
		printf("%s\n", envp[i]);
	line = readline("lexer-test$ ");
	get_token(line);
	// while (1)
	return (0);
}
