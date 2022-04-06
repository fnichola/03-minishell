/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex-init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:54:14 by fnichola          #+#    #+#             */
/*   Updated: 2022/04/06 14:23:10 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_state_func_row *init_state_func_table(void)
{
	const t_state_func_row temp[] = {
		{ST_NEUTRAL,				&lex_neutral},
		{ST_PIPE,				&lex_pipe},
		{ST_GT,					&lex_gt},
		{ST_GTGT,				&lex_gtgt},
		{ST_LT,					&lex_lt},
		{ST_LTLT,				&lex_ltlt},
		{ST_BEGIN_SINGLE_QUOTE,	&lex_begin_single_quote},
		{ST_IN_SINGLE_QUOTE,		&lex_in_single_quote},
		{ST_BEGIN_DOUBLE_QUOTE,	&lex_begin_double_quote},
		{ST_IN_DOUBLE_QUOTE,		&lex_in_double_quote},
		{ST_DOLLAR,				&lex_dollar},
		{ST_EXIT_STATUS,			&lex_exit_status},
		{ST_VARIABLE,			&lex_variable},
		{ST_IN_WORD,				*lex_in_word},
		{ST_END_OF_LINE,			*lex_end_of_line}
	};
	t_state_func_row	*state_func_table;
	state_func_table = malloc_error_check(sizeof(temp));
	ft_memcpy(state_func_table, temp, sizeof(temp));//constだとスコープがその関数内だけだが、memcpyでコピーしたアドレスはreturnできる。
	return (state_func_table);
}

void	init_lex_arg(t_lex_arg *l, char *line)
{
	l->line = line;
	l->i = 0;
	l->start_index = 0;
	l->state = ST_NEUTRAL;
	l->found_token = false;
	return ;
}
