/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:11:01 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 11:30:56 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_state {
	ST_NEUTRAL = 0,
	ST_SPECIAL,
	ST_IN_SINGLE_QUOTE,
	ST_IN_DOUBLE_QUOTE,
	ST_IN_WORD
}	t_state;

typedef struct s_lex_arg {
	const char			*line;
	char				current_char;
	char				next_char;
	size_t				index;
	size_t				start_index;
	t_state				state;
	t_state				previous_state;
	bool				found_token;
	t_token				*token;
}	t_lex_arg;

/**
 * Rows that make up the state function table.
 * Used to look up the correct function to run in each state.
 * State function table must match e_state enum list.
 */
typedef struct s_state_func_row {
	t_state	state;
	void	(*lex_func)(t_lex_arg *l);
}	t_state_func_row;

t_list				*tokenizer(const char *line);
t_state_func_row	*init_state_func_table(void);
void				init_lex_arg(t_lex_arg *l, const char *line);
bool				is_delimeter(char c);
bool				is_space(char c);
char				*token_type_to_str(t_token_type token_type);
void				change_lex_state(t_lex_arg *l, t_state new_state);
void				lex_neutral(t_lex_arg *l);
void				lex_special(t_lex_arg *l);
void				lex_in_single_quote(t_lex_arg *l);
void				lex_in_double_quote(t_lex_arg *l);
void				lex_in_word(t_lex_arg *l);
void				lex_pipe(t_lex_arg *l);
void				lex_gt(t_lex_arg *l);
void				lex_lt(t_lex_arg *l);
void				flush_to_token(t_lex_arg *l);
void				next_char(t_lex_arg *l);
void				expand_var(t_lex_arg *l);

#endif
