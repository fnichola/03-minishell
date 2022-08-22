/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:40:07 by fnichola          #+#    #+#             */
/*   Updated: 2022/08/22 19:39:31 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "env.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>

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
	T_DOUBLE_QUOTED, // double-quoted text
	T_PIPE,//
	T_GT, // >
	T_GTGT, // >>
	T_LT, // <
	T_LTLT, // <<
	T_FILE,
	T_VAR, //$ 環境変数
	T_EXIT_STATUS, //$?
	T_EOL,
	T_ERROR
}	t_token_type;

typedef struct s_token {
	char			*word;
	t_token_type	token_type;
}	t_token;

typedef struct s_str_func_table {
	char	*name;
	void	(*func)(char **argv);
}	t_str_func_table;

/**
 * Command data structure.
 * 
 * There will be one t_command variable for each command in a pipeline.
 * In minishell (without bonuses) there is no other way to have multiple
 * commands in one line.
 * 
 * argv holds an array of strings starting with the program name/path and
 * followed by its arguments.
 * 
 * output_file, input_file, and error_file are for redirection. If there is
 * no redirection, they should be set to NULL.
 */
typedef struct s_command {
	char		**argv; // = {"grep", "c", 0}
	char		*output_file; // = "test.txt"
	char		*input_file;
	char		*error_file;
	t_envlist	*env_list;
}	t_command;

typedef struct s_exec_fds {//command１つ１つに対して依存するべき
	int	in_fd;
	int	out_fd;
	int	pipe_fd[2];
}	t_exec_fds;

typedef struct s_minishell_data {
	t_str_func_table	*built_ins;
	int					num_built_ins;
	t_list				*command_table;
	int					**exec_fds;
	size_t				num_cmds;
	size_t				cmd_index;
	int					exit_satus;
	t_envlist			*env_list;
}	t_minishell_data;

t_minishell_data	g_data;

void		exit_error(char *str);
void		built_in_exit(char **argv);
void		built_in_cd(char **argv);
void		built_in_echo(char **argv);
void		built_in_pwd(char **argv);
void		built_in_env(char **argv);
void		built_in_export(char **argv);
void		*malloc_error_check(size_t size);
t_list		*parser(t_list *tokens, t_envlist *e_list);
void		ft_perror(char *perror_str);
int			ft_strcmp(char *s1, char *s2);
char		*ft_find_env(char *env_str, char **envp);
void		ft_perror(char *perror_str);
int			ft_strcmp(char *s1, char *s2);
char		*ft_wstrjoin(char *str1, char *str2);
char		*ft_wstrdup(const char *src);
t_envlist	*ft_set_env(t_envlist *env_list, char *key, char *value, int add);
char		*ft_findenv(t_envlist *elst, char *search_key);
void		put_env_asci_order(t_envlist *e_list, t_envlist *sorted);
int			check_shell_val(char *src_str);
t_envlist	*to_setenv(t_envlist *e_list, char *src_str, size_t i);
char		*ft_wsubstr(char const *s, unsigned int start, size_t len);
void		ft_puterror(char *s1, char *s2, char *s3);
t_envlist	*ft_set_env(t_envlist *env_list, char *key, char *value, int add);
t_envlist	*ft_unsetenv(t_envlist *e_list, char *unset_key);
char		*ft_echo_env(char *str, t_envlist *e_list);
char		*find_doll_env(t_envlist *e_list, char *after_doll);
int			ft_wpipe(int fd[2]);
void		ft_wexecve(char *file, char **argv, char **envp);
#endif
