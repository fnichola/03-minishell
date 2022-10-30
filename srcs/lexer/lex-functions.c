/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex-functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:58:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 14:29:35 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

bool	is_special(char c)
{
	if (c == '|' ||
		c == '>' ||
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

void	lex_lt(t_lex_arg *l)
{
	next_char(l);
	if (l->current_char == '<')
	{
		l->token->type = T_LTLT;
		next_char(l);
	}
	else
		l->token->type = T_LT;
	l->found_token = true;
}

void	lex_in_single_quote(t_lex_arg *l)
{
	next_char(l);
	l->start_index = l->index;
	while(l->current_char != '\'')
	{
		if (!l->current_char)
		{
			l->found_token = true;
			l->token->type = T_ERROR;
			ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
			return ;
		}
		next_char(l);
	}
	l->token->type = T_WORD;
	flush_to_token(l);
	next_char(l);
	l->start_index = l->index;
	change_lex_state(l, l->previous_state);
}

void	lex_in_double_quote(t_lex_arg *l)
{
	next_char(l);
	l->start_index = l->index;
	while(l->current_char != '\"')
	{
		if (!l->current_char)
		{
			l->token->type = T_ERROR;
			l->found_token = true;
			ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
			return ;
		}
		else if (l->current_char == '$' &&
			(ft_isalnum(l->next_char) || l->next_char == '?'))
		{
			flush_to_token(l);
			next_char(l);
			l->start_index = l->index;
			expand_var(l);
		}
		else
			next_char(l);
	}
	l->token->type = T_WORD;
	flush_to_token(l);
	next_char(l);
	l->start_index = l->index;
	change_lex_state(l, l->previous_state);

}
void	lex_in_word(t_lex_arg *l)
{
	if (is_delimeter(l->current_char))
	{
		l->token->type = T_WORD;
		l->found_token = true;
		flush_to_token(l);
	}
	else if (l->current_char == '\'')
	{
		flush_to_token(l);
		change_lex_state(l, ST_IN_SINGLE_QUOTE);
	}
	else if (l->current_char == '"')
	{
		flush_to_token(l);
		change_lex_state(l, ST_IN_DOUBLE_QUOTE);
	}
	else if (l->current_char == '$' &&
		(ft_isalpha(l->next_char) || l->next_char == '?'))
	{
		flush_to_token(l);
		next_char(l);
		expand_var(l);
	}
	else
		next_char(l);
}
