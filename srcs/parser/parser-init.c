/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:54:14 by fnichola          #+#    #+#             */
/*   Updated: 2022/09/30 23:12:11 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_state_func_row	*p_init_state_func_table(void)
{
	const t_state_func_row	temp[] = {
		{ST_NEUTRAL,		&parser_neutral},
		{ST_FIRST_WORD,		&parser_first_word},
		{ST_SIMPLE_COMMAND,	&parser_simple_command},
		{ST_REDIRECT,		&parser_redirect},
		{ST_ENV,			&parser_env},
		{ST_IN_DQUOTE,		&parser_in_dquote},//ここでexpandしてT_WORDに変更する
		{ST_FINISHED,	NULL}
	};
	t_state_func_row		*state_func_table;//ここでconstで初期化した構造体配列をコピーしてreturnできるようにしている。
	state_func_table = malloc_error_check(sizeof(temp));
	ft_memcpy(state_func_table, temp, sizeof(temp));//constだとスコープがその関数内だけだが、memcpyでコピーしたアドレスはreturnできる。
	return (state_func_table);
}

void	init_parse_arg(t_parse_arg *p, t_list *tokens, t_envlist *e_list)
{
	p->list_ptr = tokens;
	p->token = (t_token *)tokens->content;
	p->previous_token = NULL;
	p->state = ST_NEUTRAL;
	p->previous_state = ST_NEUTRAL;
	p->command_table = NULL;
	p->command = NULL;
	p->index = 0;
	p->e_list = e_list;
	p->count_cmds = 0;
	p->is_exit = false;
}
