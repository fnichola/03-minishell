/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex-functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:31:42 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 18:43:55 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

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
	while (l->current_char != '\'')
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

int	in_double_quote_loop(t_lex_arg *l)
{
	if (!l->current_char)
	{
		l->token->type = T_ERROR;
		l->found_token = true;
		ft_puterror("syntax error", NULL, NULL);
		return (1);
	}
	else if (l->current_char == '$' && \
		(ft_isalnum(l->next_char) || l->next_char == '?'))
	{
		flush_to_token(l);
		next_char(l);
		l->start_index = l->index;
		expand_var(l);
	}
	else
		next_char(l);
	return (0);
}

void	lex_in_double_quote(t_lex_arg *l)
{
	next_char(l);
	l->start_index = l->index;
	while (l->current_char != '\"')
	{
		if (in_double_quote_loop(l))
			return ;
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
	else if (l->current_char == '$' && \
		(ft_isalpha(l->next_char) || l->next_char == '?'))
	{
		flush_to_token(l);
		next_char(l);
		expand_var(l);
	}
	else
		next_char(l);
}
