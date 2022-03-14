/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:39:20 by fnichola          #+#    #+#             */
/*   Updated: 2022/03/14 18:01:58 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	get_token(char *line, size_t i)
{
	t_state	state;

	state = NEUTRAL;
	while (state == NEUTRAL && line[i])
	{
		if (line[i] == '|')
			return T_BAR;
		else if (line[i] == '$')
			return T_DOLLAR;
		else if (line[i] == '\n')
			return T_NL;
		else if (line[i] == '>')
		{
			state = GTGT;
			i++;
			break ;
		}
		else if (line[i] == '<')
		{
			state = LTLT;
			i++;
			break ;
		}
		else
		{
			state = IN_WORD;
			continue ;
		}
		i++;
	}
	while (state == GTGT && line[i])
	{
		if (line[i] == '>')
			return T_GTGT;
		return T_GT;
	}
	while (state == LTLT && line[i])
	{
		if (line[i] == '<')
			return T_LTLT;
		return T_LT;
	}
	while (state == IN_SINGLE_QUOTE && line[i])
	{
		if (line[i] == '\'')
			return T_WORD;
		i++;
	}
	while (state == IN_DOUBLE_QUOTE && line[i])
	{
		if (line[i] == '"')
			return T_WORD;
		i++;
	}
	while (state == IN_WORD && line[i])
	{
		if (line[i] == '|' ||
			line[i] == '<' ||
			line[i] == '>' ||
			line[i] == '\n' ||
			line[i] == ' ' ||
			line[i] == '\t')
			return T_WORD;
		i++;
	}
	return T_EOF;
}

int	main()
{
	char	*line;

	line = readline("lexer-test$ ");
	while (1)
}
