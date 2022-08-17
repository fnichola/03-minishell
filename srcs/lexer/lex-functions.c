/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex-functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:58:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/08/17 13:50:30 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	lex_neutral(t_lex_arg *l)
{
	// printf("[ST_NEUTRAL]\n");
	if (!(l->line)[l->i])
		l->state = ST_END_OF_LINE;
	else if (is_space((l->line)[l->i]))
		l->start_index = l->i + 1;
	else if ((l->line)[l->i] == '|')
		l->state = ST_PIPE;
	else if ((l->line)[l->i] == '>')
		l->state = ST_GT;
	else if ((l->line)[l->i] == '<')
		l->state = ST_LT;
	else if ((l->line)[l->i] == '\'')
		l->state = ST_BEGIN_SINGLE_QUOTE;
	else if ((l->line)[l->i] == '"')
		l->state = ST_BEGIN_DOUBLE_QUOTE;
	else if ((l->line)[l->i] == '$')
		l->state = ST_DOLLAR;
	else
		l->state = ST_IN_WORD;
}

void	lex_pipe(t_lex_arg *l)
{
	// printf("[ST_PIPE]");
	l->token_type = T_PIPE;
	l->found_token = true;
}

void	lex_gt(t_lex_arg *l)
{
	// printf("[ST_GT]\n");
	if ((l->line)[l->i] == '>')
		l->state = ST_GTGT;
	else
	{
		l->token_type = T_GT;
		l->found_token = true;
	}
}

void	lex_gtgt(t_lex_arg *l)
{
	// printf("[ST_GTGT]\n");
	l->token_type = T_GTGT;
	l->found_token = true;
}

void	lex_lt(t_lex_arg *l)
{
	// printf("[ST_LT]\n");
	if ((l->line)[l->i] == '<')
		l->state = ST_LTLT;
	else
	{
		l->token_type = T_LT;
		l->found_token = true;
	}
}

void	lex_ltlt(t_lex_arg *l)
{
	// printf("[ST_LTLT]\n");
	l->token_type = T_LTLT;
	l->found_token = true;
}

void	lex_begin_single_quote(t_lex_arg *l)
{
	// printf("[ST_BEGIN_SINGLE_QUOTE]\n");
	l->start_index = l->i;
	l->i--;
	l->state = ST_IN_SINGLE_QUOTE;
}

void	lex_in_single_quote(t_lex_arg *l)
{
	// printf("[ST_IN_SINGLE_QUOTE]\n");
	if ((l->line)[l->i] == '\'')
	{
		l->token_type = T_WORD;
		l->found_token = true;
	}
}

void	lex_begin_double_quote(t_lex_arg *l)
{
	// printf("[ST_BEGIN_DOUBLE_QUOTE]\n");
	l->start_index = l->i;
	l->i--;
	l->state = ST_IN_DOUBLE_QUOTE;
}

void	lex_in_double_quote(t_lex_arg *l)
{
	// printf("[ST_IN_DOUBLE_QUOTE]\n");
	if ((l->line)[l->i] == '"')
	{
		l->token_type = T_DOUBLE_QUOTED;//T_WORDではなくT_DQUOTEDというタイプにした
		l->found_token = true;
	}
}

void	lex_dollar(t_lex_arg *l)
{
	printf("[ST_DOLLAR]");
	if (is_delimeter((l->line)[l->i]))
	{
		l->token_type = T_WORD;
		l->found_token = true;
	}
	else if ((l->line)[l->i] == '?')
		l->state = ST_EXIT_STATUS;
	else
	{
		l->start_index = l->i;
		l->state = ST_VARIABLE;
	}
}

void	lex_exit_status(t_lex_arg *l)
{
	// printf("[ST_EXIT_STATUS]");
	l->token_type = T_EXIT_STATUS;
	l->found_token = true;
}

void	lex_variable(t_lex_arg *l)
{
	// printf("[ST_VARIABLE]\n");
	if (is_delimeter((l->line)[l->i]))
	{
		l->token_type = T_VAR;
		l->found_token = true;
	}
}

void	lex_in_word(t_lex_arg *l)
{
	// printf("[ST_IN_WORD]\n");
	if (is_delimeter((l->line)[l->i]))
	{
		l->token_type = T_WORD;
		l->found_token = true;
	}
}

void	lex_end_of_line(t_lex_arg *l)
{
	// printf("[ST_END_OF_LINE]\n");
	l->token_type = T_EOL;
	l->found_token = true;
}
