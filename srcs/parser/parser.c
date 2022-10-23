/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:02:55 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/23 02:22:42 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/**
 * Take a list of tokens (from tokenizer) and create a command table.
 * 
 * The command table has one list item for each command separated by pipes.
 * (e.g. `ls dir | grep something` has two commands)
 */
void parser(t_list *tokens)
{
	t_state_func_row	*state_func_table;
	t_parse_arg			p;

	if (!tokens)
		return ;
	state_func_table = p_init_state_func_table();//stateと関数ポインタを作成している。
	init_parse_arg(&p, tokens);
	p.list_ptr = tokens;//ここでtoken(単語)のリストを渡している
	while (p.state != ST_FINISHED)
	{
		state_func_table[p.state].parse_func(&p);//構造体ないの関数ポインタを実行している
	}
	free(state_func_table);
	if (p.previous_token)
		if (p.previous_token->type == T_GT ||
			p.previous_token->type == T_GTGT ||
			p.previous_token->type == T_LT ||
			p.previous_token->type == T_LTLT ||
			p.previous_token->type == T_PIPE)
		{
			ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
			free_command_table();
		}
	ft_lstclear(&tokens, del_token);
}
