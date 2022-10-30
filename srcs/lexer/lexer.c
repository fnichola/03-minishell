/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:02:55 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 18:26:53 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	reset_lex_arg(t_lex_arg *l, t_token **token)
{
	l->state = ST_NEUTRAL;
	l->previous_state = ST_NEUTRAL;
	l->start_index = l->index;
	l->current_char = (l->line)[l->index];
	l->found_token = false;
	l->token = *token;
	l->token->type = T_ERROR;
	l->token->word = NULL;
}

/**
 * Returns the next token from the string "line".
 * e.g.
 * <T_WORD> "ls"
 */
int	get_next_token(t_lex_arg *l,
	const t_state_func_row *state_func_table,
	t_token **token)
{
	reset_lex_arg(l, token);
	while (!l->found_token)
	{
		state_func_table[l->state].lex_func(l);
		if (l->found_token)
		{
			if (l->token->type == T_EOL)
			{
				free(l->token);
				*token = NULL;
			}
			else if (l->token->type == T_ERROR)
			{
				free(l->token->word);
				return (1);
			}
			else if (l->token->type == T_WORD && !l->token->word)
			{
				l->found_token = false;
				change_lex_state(l, ST_NEUTRAL);
			}
		}
	}
	return (0);
}

/**
 * Returns a list of all tokens in the string "line".
 * e.g.:
 * <T_WORD>	"ls"
 * <T_WORD>	"dir"
 * <T_PIPE>	"|"
 * <T_WORD>	"grep"
 * <T_WORD> "something"
 */
t_list	*tokenizer(const char *line)
{
	t_state_func_row	*state_func_table;
	t_token				*new_token;
	t_list				*token_list;
	t_lex_arg			l;

	new_token = malloc_error_check(sizeof(t_token));
	token_list = NULL;
	state_func_table = init_state_func_table();
	init_lex_arg(&l, line);
	if (get_next_token(&l, state_func_table, &new_token))
		return (NULL);
	while (new_token)
	{
		ft_lstadd_back(&token_list, ft_lstnew(new_token));
		new_token = malloc_error_check(sizeof(t_token));
		if (get_next_token(&l, state_func_table, &new_token))
		{
			ft_lstclear(&token_list, del_token);
			token_list = NULL;
			free(new_token);
			break ;
		}
	}
	free(state_func_table);
	return (token_list);
}
