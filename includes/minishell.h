/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:40:07 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/16 14:14:11 by fnichola         ###   ########.fr       */
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
# include <fcntl.h>

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
	T_LT,
	T_LTLT,
	T_VAR, //$ 環境変数
	T_EXIT_STATUS, //$?
	T_EOL,
	T_ERROR
}	t_token_type;

typedef struct s_token {
	char			*word;
	t_token_type	type;
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

typedef enum e_redirect_type {
	UNDEFINED_REDIRECT,
	OUTPUT_REDIRECT,
	INPUT_REDIRECT
}	t_redirect_type;

typedef struct s_redirect {
	t_redirect_type	type;
	bool				append;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command {
	char				**argv; // = {"grep", "c", 0}
	t_redirect			*redirects;
	pid_t				pid;
	int					input_fd;
	int					output_fd;
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

typedef struct s_exec_fds {//command１つ１つに対して依存するべき
	int	in_fd;
	int	out_fd;
	int	pipe_fd[2];
}	t_exec_fds;

typedef struct s_minishell_data {
	t_str_func_table	*built_ins;
	size_t				num_built_ins;
	t_command			*command_table;
	size_t				cmd_index;
	int					exit_satus;
	t_envlist			*env_list;
}	t_minishell_data;

extern t_minishell_data	g_data;
extern bool	g_debug;

void		debug_log(const char *format, ...);
void		exit_error(char *str);
void		error_command(char *str1, char *str2, char *str3);
void		init_built_in_table(void);
void		built_in_exit(char **argv);
void		built_in_cd(char **argv);
void		built_in_echo(char **argv);
void		built_in_pwd(char **argv);
void		built_in_env(char **argv);
void		built_in_export(char **argv);
bool		is_valid_variable(char *variable);
bool		is_str_match(const char *s1, const char *s2);
char		*str_tolower(char *str);
void		*malloc_error_check(size_t size);
void		parser(t_list *tokens);
void		ft_perror(char *perror_str);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_wstrjoin(char *str1, char *str2);
char		*ft_wstrdup(const char *src);
char		*ft_wsubstr(char const *s, unsigned int start, size_t len);
int			ft_strncpy(char *dest, char *src, size_t cpy_len);
void		ft_puterror(char *s1, char *s2, char *s3);
char		*ft_echo_env(char *str, t_envlist *e_list);
int			ft_wpipe(int fd[2]);
void		ft_wexecve(char *file, char **argv, char **envp);
int			execute_commands(void);
void		prepare_exec_fds(void);
void		free_exec_fds(void);
void		free_command(t_command *cmd);
void		close_exec_fds(void);
t_envlist	*env_list_copy_all(t_envlist *node);
t_envlist	*env_list_dup(t_envlist *node);
t_envlist	*env_list_first(t_envlist *ptr);
t_envlist	*env_list_last(t_envlist *ptr);
t_envlist	*env_list_new(char *name, char *value, char *string);
size_t		env_list_size(t_envlist *node);
t_envlist	*env_list_sort(t_envlist *env_list);
void		env_list_swap_next(t_envlist *node);
char		*env_to_string(const char *name, const char *value);
char		**export_to_envp(void);
void		free_env_list(t_envlist **env_list);
void		free_envp(char **envp);
t_envlist	*ft_findenv(const char *name);
char		*ft_getenv(char *name);
int			ft_setenv(const char *name, const char *value, int overwrite);
t_envlist	*ft_unsetenv(t_envlist *e_list, char *unset_key);
char		*get_env_name(char *env);
char		*get_env_value(char *env);
void		init_env_list(char **envp);
t_envlist	split_env(const char *str);
t_redirect	*redirect_new(void);
t_redirect	*redirect_add(t_redirect **redirect_list, t_redirect *new_redirect);
void		free_redirects(t_redirect **redirect_list);
void		command_add_back(t_command *new_command);
void		free_command(t_command *cmd);
void		free_command_table(void);
t_command	*del_command(t_command *cmd);

#endif
