/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:40:07 by fnichola          #+#    #+#             */
/*   Updated: 2022/04/19 16:52:15 by fnichola         ###   ########.fr       */
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
 * Token types returned by tokenizer(). Input from readline is broken into
 * tokens and each token has a type.
 * 
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

typedef struct s_token {
	char			*word;
	t_token_type	token_type;
}	t_token;

/**
 * The command table data structure.
 * All of the simple commands in the list "simple_commands" will be piped
 * together. A simple command is an array of words to be passed to execve
 * (i.e. char **argv).
 * 
 * output_file, input_file, and error_file are for redirection. If there is
 * no redirection, they should be set to NULL.
 */
typedef struct s_command {
	t_list	*simple_commands;
	char	*output_file;
	char	*input_file;
	char	*error_file;
}	t_command;

void	exit_error(char *str);
void	*malloc_error_check(size_t size);

#endif
