/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:11:01 by fnichola          #+#    #+#             */
/*   Updated: 2022/04/06 14:21:03 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <errno.h>

/**
 * T_WORD = word
 * T_PIPE = |
 * T_GT = >
 * T_GTGT = >
 * T_LT = <
 * T_LTLT = <<
 * T_VAR = $
 * T_EXIT_STATUS = $?
 * T_ERROR = error
 */
typedef enum e_token_type {
	T_WORD, //alphabet
	T_PIPE,//
	T_GT,
	T_GTGT,
	T_LT,
	T_LTLT,
	T_VAR, //$
	T_EXIT_STATUS, //$?
	T_EOL,
	T_ERROR
}	t_token_type;

typedef enum e_state {
	ST_NEUTRAL = 0,
	ST_PIPE,
	ST_GT,
	ST_GTGT,
	ST_LT,
	ST_LTLT,
	ST_BEGIN_SINGLE_QUOTE,
	ST_IN_SINGLE_QUOTE,
	ST_BEGIN_DOUBLE_QUOTE,
	ST_IN_DOUBLE_QUOTE,
	ST_DOLLAR,
	ST_EXIT_STATUS,
	ST_VARIABLE,//$
	ST_IN_WORD,//alphabet
	ST_END_OF_LINE
}	t_state;

typedef struct s_token {
	char			*word;
	t_token_type	token_type;
}	t_token;

typedef struct s_lex_arg {
	char				*line;
	size_t				i;
	size_t				start_index;//tokenの開始インデックスで最初の空白は無視
	t_state				state;//
	t_token_type		token_type;//関数ポインタの中で設定してあげる。
	bool				found_token;
}	t_lex_arg;

/**
 * Rows that make up the state function table.
 * Used to look up the correct function to run in each state.
 * State function table must match e_state enum list.
 */
typedef struct s_state_func_row {
	t_state		state;
	void 		(*lex_func)(t_lex_arg *l);
}	t_state_func_row;


t_state_func_row	*init_state_func_table(void);
void	init_lex_arg(t_lex_arg *l, char *line);
void	del_token(void *token_ptr);
bool	is_delimeter(char c);
bool	is_space(char c);
char	*token_type_to_str(t_token_type token_type);

void	lex_neutral(t_lex_arg *l);
void	lex_pipe(t_lex_arg *l);
void	lex_gt(t_lex_arg *l);
void	lex_gtgt(t_lex_arg *l);
void	lex_lt(t_lex_arg *l);
void	lex_ltlt(t_lex_arg *l);
void	lex_begin_single_quote(t_lex_arg *l);
void	lex_in_single_quote(t_lex_arg *l);
void	lex_begin_double_quote(t_lex_arg *l);
void	lex_in_double_quote(t_lex_arg *l);
void	lex_dollar(t_lex_arg *l);
void	lex_exit_status(t_lex_arg *l);
void	lex_variable(t_lex_arg *l);
void	lex_in_word(t_lex_arg *l);
void	lex_end_of_line(t_lex_arg *l);

#endif
