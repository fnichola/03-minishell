/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex-functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:58:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/04/05 17:04:25 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	lex_neutral(t_lex_arg *l)
{
	printf("[NEUTRAL]\n");
	if (!(l->line)[l->i])
		l->state = END_OF_LINE;
	else if (is_space((l->line)[l->i]))
	{
		l->start_index = l->i + 1;
		l->state = NEUTRAL;
	}
	else if ((l->line)[l->i] == '>')
		l->state = GTGT;
	else if ((l->line)[l->i] == '<')
		l->state = LTLT;
	else if ((l->line)[l->i] == '\'')
		l->state = BEGIN_SINGLE_QUOTE;
	else if ((l->line)[l->i] == '"')
		l->state = BEGIN_DOUBLE_QUOTE;
	else if ((l->line)[l->i] == '$')
	{
		l->start_index = l->i + 1;
		l->state = VARIABLE;
	}
	else
		l->state = IN_WORD;
}

void	lex_gtgt(t_lex_arg *l)
{
	printf("[GTGT]\n");
	if ((l->line)[l->i] == '>')
		l->token_type = T_GTGT;
	else	
		l->token_type = T_GT;
	l->found_token = true;
}

void	lex_ltlt(t_lex_arg *l)
{
	printf("[LTLT]\n");
	if ((l->line)[l->i] == '<')
		l->token_type = T_LTLT;
	else	
		l->token_type = T_LT;
	l->found_token = true;

}

void	lex_begin_single_quote(t_lex_arg *l)
{
	printf("[BEGIN_SINGLE_QUOTE]\n");
	l->start_index = l->i;
	l->i--;
	l->state = IN_SINGLE_QUOTE;
}

void	lex_in_single_quote(t_lex_arg *l)
{
	printf("[IN_SINGLE_QUOTE]\n");
	if ((l->line)[l->i] == '\'')
	{
		l->token_type = T_WORD;
		l->found_token = true;
	}
}

void	lex_begin_double_quote(t_lex_arg *l)
{
	printf("[BEGIN_DOUBLE_QUOTE]\n");
	l->start_index = l->i;
	l->i--;
	l->state = IN_DOUBLE_QUOTE;
}

void	lex_in_double_quote(t_lex_arg *l)
{
	printf("[IN_DOUBLE_QUOTE]\n");
	if ((l->line)[l->i] == '"')
	{
		l->token_type = T_WORD;
		l->found_token = true;
	}
}

void	lex_variable(t_lex_arg *l)
{
	printf("[IN_DOUBLE_QUOTE]\n");
	if (is_delimeter((l->line)[l->i]) || !(l->line)[l->i])
	{
		l->token_type = T_VAR;
		l->found_token = true;
	}
}

void	lex_in_word(t_lex_arg *l)
{
	printf("[IN_WORD]\n");
	if (is_delimeter((l->line)[l->i]) || !(l->line)[l->i])
	{
		l->token_type = T_WORD;
		l->found_token = true;
	}
}

void	lex_end_of_line(t_lex_arg *l)
{
	printf("[END_OF_LINE]\n");
	l->token_type = T_EOL;
	l->found_token = true;
}
