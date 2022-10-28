/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:11:01 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/28 18:20:31 by akihito          ###   ########.fr       */
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
	ST_START_WORD,
	ST_SIMPLE_COMMAND,
	ST_REDIRECT,
	ST_ENV,
	ST_IN_DQUOTE,
	ST_FINISHED,
}	t_state;

typedef struct s_parse_arg {
	t_list			*list_ptr;//ここ使ってなくないですか？
	t_token			*token;
	t_token			*previous_token;
	t_state			state;
	t_state			previous_state;
	t_command		*command;//ここでコマンド
	size_t			index;
	t_envlist		*e_list;
	size_t			count_cmds;
	bool			is_exit;// parser_redirectでファイルの権限がない場合は、exitしないといけないが、もし親プロセス（パイプなしbuiltin)だったらminishell自体が終了してしまうのでこのメンバ変数を追加。使い所はわからない
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

// t_list	*parser(t_list *tokens);
t_state_func_row	*p_init_state_func_table(void);
void	init_parse_arg(t_parse_arg *p, t_list *tokens);
void	parser_neutral(t_parse_arg *p);
void	parser_start_word(t_parse_arg *p);
void	parser_simple_command(t_parse_arg *p);
void	parser_redirect(t_parse_arg *p);
void	parser_env (t_parse_arg *p);
void	parser_in_dquote (t_parse_arg *p);
void	expand_quoted_text(t_parse_arg *p);
int		add_list(int value, size_t count_cmds, t_redirect *nil);
t_redirect	*init_redirect_nil();
#endif
