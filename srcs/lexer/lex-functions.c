/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex-functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:58:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 16:44:08 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

bool	is_special(char c)
{
	if (c == '|' || \
		c == '>' || \
		c == '<')
		return (true);
	return (false);
}

void	lex_neutral(t_lex_arg *l)
{
	if (!l->current_char)
	{
		l->token->type = T_EOL;
		l->found_token = true;
	}
	else if (is_special(l->current_char))
		change_lex_state(l, ST_SPECIAL);
	else if (is_space(l->current_char))
		next_char(l);
	else
	{
		l->start_index = l->index;
		change_lex_state(l, ST_IN_WORD);
	}
}

void	lex_special(t_lex_arg *l)
{
	if (l->current_char == '|')
		lex_pipe(l);
	else if (l->current_char == '>')
		lex_gt(l);
	else if (l->current_char == '<')
		lex_lt(l);
}

void	lex_pipe(t_lex_arg *l)
{
	next_char(l);
	l->token->type = T_PIPE;
	l->found_token = true;
}

void	lex_gt(t_lex_arg *l)
{
	next_char(l);
	if (l->current_char == '>')
	{
		l->token->type = T_GTGT;
		next_char(l);
	}
	else
		l->token->type = T_GT;
	l->found_token = true;
}
