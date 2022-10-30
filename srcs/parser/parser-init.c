/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:54:14 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 15:30:14 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_state_func_row	*p_init_state_func_table(void)
{
	const t_state_func_row	temp[] = {
	{ST_NEUTRAL,		&parser_neutral},
	{ST_START_WORD,		&parser_start_word},
	{ST_SIMPLE_COMMAND,	&parser_simple_command},
	{ST_REDIRECT,		&parser_redirect},
	{ST_ENV,			&parser_env},
	{ST_IN_DQUOTE,		&parser_in_dquote},
	{ST_FINISHED,	NULL}
	};
	t_state_func_row		*state_func_table;

	state_func_table = malloc_error_check(sizeof(temp));
	ft_memcpy(state_func_table, temp, sizeof(temp));
	return (state_func_table);
}

void	init_parse_arg(t_parse_arg *p, t_list *tokens)
{
	p->list_ptr = tokens;
	if (tokens && tokens->content)
		p->token = (t_token *)tokens->content;
	else
		p->token = NULL;
	p->previous_token = NULL;
	p->state = ST_NEUTRAL;
	p->previous_state = ST_NEUTRAL;
	p->command = NULL;
	p->index = 0;
	p->count_cmds = 0;
	p->is_exit = false;
}
