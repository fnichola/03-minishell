/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex-functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:58:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/17 13:46:25 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	lex_neutral(t_lex_arg *l)
{
	debug_log("[ST_NEUTRAL]\n");
	if (!l->current_char)
		l->state = ST_END_OF_LINE;
	else if (is_space(l->current_char))
		next_char(l);
	else
		l->state = ST_START_TOKEN;
}

void	lex_start_word(t_lex_arg *l)
{
	debug_log("[ST_START_WORD]\n");
	l->start_index = l->index;
	if (l->current_char == '|')
		l->state = ST_PIPE;
	else if (l->current_char == '>')
		l->state = ST_GT;
	else if (l->current_char == '<')
		l->state = ST_LT;
	else if (l->current_char == '\'')
		l->state = ST_BEGIN_SINGLE_QUOTE;
	else if (l->current_char == '"')
		l->state = ST_BEGIN_DOUBLE_QUOTE;
	else if (l->current_char == '$')
		l->state = ST_DOLLAR;
	else
		l->state = ST_IN_WORD;
}

void	lex_pipe(t_lex_arg *l)
{
	debug_log("[ST_PIPE]");
	next_char(l);
	l->token->type = T_PIPE;
	l->found_token = true;
}

void	lex_gt(t_lex_arg *l)
{
	// debug_log("[ST_GT]\n");
	next_char(l);
	if (l->current_char == '>')
		l->state = ST_GTGT;
	else
	{
		l->token->type = T_GT;
		l->found_token = true;
	}
}

void	lex_gtgt(t_lex_arg *l)
{
	// debug_log("[ST_GTGT]\n");
	next_char(l);
	l->token->type = T_GTGT;
	l->found_token = true;
}

void	lex_lt(t_lex_arg *l)
{
	// debug_log("[ST_LT]\n");
	next_char(l);
	if (l->current_char == '<')
		l->state = ST_LTLT;
	else
	{
		l->token->type = T_LT;
		l->found_token = true;
	}
}

void	lex_ltlt(t_lex_arg *l)
{
	// debug_log("[ST_LTLT]\n");
	next_char(l);
	l->token->type = T_LTLT;
	l->found_token = true;
}

void	lex_begin_single_quote(t_lex_arg *l)
{
	debug_log("[ST_BEGIN_SINGLE_QUOTE]\n");
	next_char(l);
	l->start_index = l->index;
	l->state = ST_IN_SINGLE_QUOTE;
}

void	lex_in_single_quote(t_lex_arg *l)
{
	debug_log("[ST_IN_SINGLE_QUOTE]\n");
	if (l->current_char == '\'')
	{
		l->token->type = T_WORD;
		join_substr_to_token(l);
		next_char(l);
		l->start_index = l->index;
		l->state = ST_IN_WORD;
	}
	else if (is_delimeter(l->current_char))
	{
		printf("SYNTAX ERROR\n");
		l->token->type = T_ERROR;
		l->found_token = true;
	}
	else
		next_char(l);
}

void	lex_begin_double_quote(t_lex_arg *l)
{
	debug_log("[ST_BEGIN_DOUBLE_QUOTE]\n");
	next_char(l);
	l->start_index = l->index;
	l->state = ST_IN_DOUBLE_QUOTE;
}

void	lex_in_double_quote(t_lex_arg *l)
{
	debug_log("[ST_IN_DOUBLE_QUOTE]\n");
	if (l->current_char == '\"')
	{
		l->token->type = T_WORD;
		join_substr_to_token(l);
		next_char(l);
		l->start_index = l->index;
		l->state = ST_IN_WORD;
	}
	else if (is_delimeter(l->current_char))
	{
		printf("SYNTAX ERROR\n");
		l->token->type = T_ERROR;
		l->found_token = true;
	}
	else
		next_char(l);
}

void	lex_dollar(t_lex_arg *l)
{
	debug_log("[ST_DOLLAR]\n");
	if (is_delimeter(l->current_char))
	{
		l->token->type = T_WORD;
		l->found_token = true;
	}
	else if (l->current_char == '?')
		l->state = ST_EXIT_STATUS;
	else
	{
		l->start_index = l->index;
		l->state = ST_VARIABLE;
	}
}

void	lex_exit_status(t_lex_arg *l)
{
	debug_log("[ST_EXIT_STATUS]");
	l->token->type = T_EXIT_STATUS;
	l->found_token = true;
}

void	lex_variable(t_lex_arg *l)
{
	debug_log("[ST_VARIABLE]\n");
	if (is_delimeter(l->current_char))
	{
		l->token->type = T_VAR;
		l->found_token = true;
	}
}

void	lex_in_word(t_lex_arg *l)
{
	debug_log("[ST_IN_WORD]\n");
	if (is_delimeter(l->current_char))
	{
		l->token->type = T_WORD;
		l->found_token = true;
		join_substr_to_token(l);
	}
	else if (l->current_char == '\'')
	{
		join_substr_to_token(l);
		l->state = ST_BEGIN_SINGLE_QUOTE;
	}
	else if (l->current_char == '"')
	{
		join_substr_to_token(l);
		l->state = ST_BEGIN_DOUBLE_QUOTE;
	}
	else if (l->current_char == '$')
		l->state = ST_DOLLAR;
	else
		next_char(l);
}

void	lex_end_of_line(t_lex_arg *l)
{
	debug_log("[ST_END_OF_LINE]\n");
	free(l->token);
	l->token = NULL;
	l->found_token = true;
}
