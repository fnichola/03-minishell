/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:40:07 by fnichola          #+#    #+#             */
/*   Updated: 2022/03/23 17:04:46 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>

/**
 * T_WORD = word
 * T_PIPE = |
 * T_GT = >
 * T_GTGT = >
 * T_LT = <
 * T_LTLT = <<
 * T_VAR = $
 * T_PID = $$
 * T_EXIT_STATUS = $?
 * T_ERROR = error
 */
typedef enum e_token_type {
	T_WORD, 
	T_PIPE,
	T_GT,
	T_GTGT,
	T_LT,
	T_LTLT,
	T_VAR,
	T_PID,
	T_EXIT_STATUS,
	T_ERROR
}	t_token_type;

typedef enum e_state {
	NEUTRAL,
	GTGT,
	LTLT,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE,
	VARIABLE,
	IN_WORD
}	t_state;

typedef struct s_token {
	char			*word;
	t_token_type	token_type;
}	t_token;

typedef struct s_state_func_row {
	const char	*state_name;
	void 		(*func)(void);
}	t_state_func_row;

static t_state_func_row state_func_test[] = {
	{"NEUTRAL", &lex_neutral},
	{"GTGT", &lex_gtgt},
	{"LTLT", &lex_ltlt},
	{"IN_SINGLE_QUOTE", &lex_single_quote},
	{"IN_DOUBLE_QUOTE", &lex_double_quote},
	
}

#endif
