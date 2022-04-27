/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:11:01 by fnichola          #+#    #+#             */
/*   Updated: 2022/04/19 22:01:14 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "minishell.h"
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>

typedef enum e_state {
	ST_NEUTRAL = 0,
	ST_FIRST_WORD,
	ST_SIMPLE_COMMAND,
	ST_REDIRECT,
	ST_FINISHED
}	t_state;

typedef struct s_parse_arg {
	t_list			*list_ptr;
	t_token			*token;
	t_token			*previous_token;
	t_state			state;
	t_state			previous_state;
	t_list			*command_table;
	t_command		*command;
	size_t			index;
}	t_parse_arg;

/**
 * Rows that make up the state function table.
 * Used to look up the correct function to run in each state.
 * State function table must match e_state enum list.
 */
typedef struct s_state_func_row {
	t_state		state;
	void 		(*parse_func)(t_parse_arg *l);
}	t_state_func_row;

t_list	*parser(t_list *tokens);
t_state_func_row	*p_init_state_func_table(void);
void	init_parse_arg(t_parse_arg *p, t_list *tokens);

void	parser_neutral(t_parse_arg *p);
void	parser_first_word(t_parse_arg *p);
void	parser_simple_command(t_parse_arg *p);

#endif