/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:02:55 by fnichola          #+#    #+#             */
/*   Updated: 2022/06/30 22:22:23 by akihito          ###   ########.fr       */
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
	p.list_ptr = tokens;
	while (p.state != ST_FINISHED)//ここで、終了ステータスが2の時に無限ループする
	{
		// printf("parser");
		printf("p.state %d\n", p.state);
		p.previous_state = p.state;
		state_func_table[p.state].parse_func(&p);
	}
	free(state_func_table);
	ft_lstclear(&tokens, del_token);
	return (p.command_table);
}
