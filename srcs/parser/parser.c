/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:02:55 by fnichola          #+#    #+#             */
/*   Updated: 2022/08/17 15:31:02 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	del_token(void *token_ptr)
{
	t_token	*token;

	token = (t_token *)token_ptr;
	if (token)
	{
		free(token->word);
		token->word = NULL;
		free(token);
		token = NULL;
	}
}

/**
 * Take a list of tokens (from tokenizer) and create a command table.
 * 
 * The command table has one list item for each command separated by pipes.
 * (e.g. `ls dir | grep something` has two commands)
 */
t_list	*parser(t_list *tokens)
{
	t_state_func_row	*state_func_table;
	t_parse_arg			p;

	state_func_table = p_init_state_func_table();//stateと関数ポインタを作成している。
	init_parse_arg(&p, tokens);
	p.list_ptr = tokens;//ここでtoken(単語)のリストを渡している
	while (p.state != ST_FINISHED)
	{
		// printf("実行");
		printf(" p.state  %u\n", p.state);
		state_func_table[p.state].parse_func(&p);//構造体ないの関数ポインタを実行している
	}
	free(state_func_table);
	ft_lstclear(&tokens, del_token);
	return (p.command_table);
}
