/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:11:01 by fnichola          #+#    #+#             */
/*   Updated: 2022/08/28 19:23:02 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "minishell.h"
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>

typedef enum e_state {
	ST_NEUTRAL = 0,
	ST_FIRST_WORD,
	ST_SIMPLE_COMMAND,
	ST_GT,
	ST_GTGT,
	ST_LT,
	ST_LTLT,
	ST_FILE,
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
	t_list			*command_table;
	t_command		*command;
	size_t			index;
	t_envlist		*e_list;
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

// t_list	*parser(t_list *tokens);
t_state_func_row	*p_init_state_func_table(void);
void	init_parse_arg(t_parse_arg *p, t_list *tokens, t_envlist *e_list);
void	parser_neutral(t_parse_arg *p);
void	parser_first_word(t_parse_arg *p);
void	parser_simple_command(t_parse_arg *p);
void	parser_env (t_parse_arg *p);
void	parser_in_dquote (t_parse_arg *p);
void	parser_gt(t_parse_arg *p);
void	parser_gtgt(t_parse_arg *p);
void	change_state(t_parse_arg *p, t_state new_state);
void	next_token(t_parse_arg *p);
void	expand_quoted_text(t_parse_arg *p);
void	set_redirect(t_parse_arg *p);
void	parser_lt(t_parse_arg *p);
void	parser_ltlt(t_parse_arg *p);
void	parser_file(t_parse_arg *p);
void	operation_file_fds(t_parse_arg *p);
int		is_file_exist(t_parse_arg *p, char *file_name);

#endif
