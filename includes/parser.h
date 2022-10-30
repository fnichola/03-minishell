/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:11:01 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 15:32:47 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_state {
	ST_NEUTRAL = 0,
	ST_START_WORD,
	ST_SIMPLE_COMMAND,
	ST_REDIRECT,
	ST_ENV,
	ST_IN_DQUOTE,
	ST_FINISHED,
}	t_state;

typedef struct s_parse_arg {
	t_list			*list_ptr;
	t_token			*token;
	t_token			*previous_token;
	t_state			state;
	t_state			previous_state;
	t_command		*command;
	size_t			index;
	t_envlist		*e_list;
	size_t			count_cmds;
	bool			is_exit;
}	t_parse_arg;

/**
 * Rows that make up the state function table.
 * Used to look up the correct function to run in each state.
 * State function table must match e_state enum list.
 */
typedef struct s_state_func_row {
	t_state		state;
	void		(*parse_func)(t_parse_arg *l);
}	t_state_func_row;

t_state_func_row	*p_init_state_func_table(void);
void				init_parse_arg(t_parse_arg *p, t_list *tokens);
void				parser_neutral(t_parse_arg *p);
void				parser_start_word(t_parse_arg *p);
void				parser_simple_command(t_parse_arg *p);
void				parser_redirect(t_parse_arg *p);
void				parser_env(t_parse_arg *p);
void				parser_in_dquote(t_parse_arg *p);
void				expand_quoted_text(t_parse_arg *p);
int					add_list(int value, size_t count_cmds, t_redirect *nil);
void				next_token(t_parse_arg *p);
void				change_state(t_parse_arg *p, t_state new_state);
void				init_command(t_parse_arg *p);
bool				is_redirect_token(t_token_type t);
void				parser_neutral(t_parse_arg *p);
#endif
