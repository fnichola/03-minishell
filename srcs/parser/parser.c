/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:02:55 by fnichola          #+#    #+#             */
/*   Updated: 2022/04/19 21:58:53 by fnichola         ###   ########.fr       */
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
t_list	*parser(t_list *tokens)
{
	t_state_func_row	*state_func_table;
	t_parse_arg			p;

	state_func_table = p_init_state_func_table();//stateと関数ポインタを作成している。
	init_parse_arg(&p, tokens);
	p.list_ptr = tokens;
	while (p.state != ST_FINISHED)
	{
		p.previous_state = p.state;
		state_func_table[p.state].parse_func(&p);
	}
	free(state_func_table);
	return (p.command_table);
}




// // t_list command_table

// typedef struct s_list
// {
// 	void			*content; ---> t_command *
// 	struct s_list	*next;
// }					t_list;

// typedef struct s_command {
// 	char	**argv; // = {"grep", "c", 0}
// 	char	*output_file; // = "test.txt"
// 	char	*input_file;
// 	char	*error_file;
// }	t_command;

// command_table->content->argv = {"ls", 0}
// command_table->next->content->argv = {"grep", "c", 0}


// recursive_exec(command_table) // ls
// {
// 	// redirect の準備 dup2()
// 	// pipe のつながり pipe()
// 	if (command_table->next)
// 		recursive_exec(command_table->next);
// 	execve(...); // ls
// 	return ;
// }
// recursive_exec(command_table) // grep c
// {
// 	// redirect の準備 dup2()
// 	// pipe のつながり pipe()
// 	if (command_table->next)
// 		recursive_exec(command_table->next);
// 	execve(...); // grep c
// 	return ;
// }

// 準備：ls -> grep c
// 実行：grep c -> ls
