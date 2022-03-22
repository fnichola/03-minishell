/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:40:07 by fnichola          #+#    #+#             */
/*   Updated: 2022/03/22 16:20:06 by fnichola         ###   ########.fr       */
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
	T_WORD, 
	T_PIPE,
	T_GT,
	T_GTGT,
	T_LT,
	T_LTLT,
	T_VAR,
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

void	exit_error(char *str);
void	*malloc_error_check(size_t size);

#endif
