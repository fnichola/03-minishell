/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex-init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:54:14 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 16:26:23 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_state_func_row	*init_state_func_table(void)
{
	const t_state_func_row	temp[] = {
	{ST_NEUTRAL,			&lex_neutral},
	{ST_SPECIAL,			&lex_special},
	{ST_IN_SINGLE_QUOTE,	&lex_in_single_quote},
	{ST_IN_DOUBLE_QUOTE,	&lex_in_double_quote},
	{ST_IN_WORD,			*lex_in_word}
	};
	t_state_func_row		*state_func_table;

	state_func_table = malloc_error_check(sizeof(temp));
	ft_memcpy(state_func_table, temp, sizeof(temp));
	return (state_func_table);
}

void	init_lex_arg(t_lex_arg *l, const char *line)
{
	l->line = line;
	l->index = 0;
	l->start_index = 0;
	l->state = ST_NEUTRAL;
	l->found_token = false;
	l->token = NULL;
	l->current_char = (l->line)[0];
	if (l->current_char)
		l->next_char = (l->line)[1];
	return ;
}
