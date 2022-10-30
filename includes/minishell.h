/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:40:07 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 18:47:47 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include "../libft/libft.h"
# include "env.h"

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
	T_WORD,
	T_DOUBLE_QUOTED,
	T_PIPE,
	T_GT,
	T_GTGT,
	T_LT,
	T_LTLT,
	T_VAR,
	T_EXIT_STATUS,
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
	t_redirect_type		type;
	bool				append;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command {
	char				**argv;
	t_redirect			*redirects;
	pid_t				pid;
	int					input_fd;
	int					output_fd;
	char				**heredoc;
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

typedef struct s_exec_fds {
	int	in_fd;
	int	out_fd;
	int	pipe_fd[2];
}	t_exec_fds;

typedef struct s_minishell_data {
	t_str_func_table	*built_ins;
	size_t				num_built_ins;
	t_command			*command_table;
	size_t				cmd_index;
	int					exit_status;
	t_envlist			*env_list;
	size_t				built_in_count;
	bool				sig_int;
}	t_minishell_data;

extern t_minishell_data	g_data;

void		exit_error(char *str);
void		init_built_in_table(void);
void		built_in_exit(char **argv);
void		built_in_cd(char **argv);
void		built_in_echo(char **argv);
void		built_in_pwd(char **argv);
void		built_in_env(char **argv);
void		built_in_export(char **argv);
void		built_in_unset(char **argv);
bool		is_valid_variable(char *variable);
bool		is_str_match(const char *s1, const char *s2);
char		*str_tolower(char *str);
void		*malloc_error_check(size_t size);
void		parser(t_list *tokens);
void		ft_perror(char *perror_str);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_wstrjoin(char *str1, const char *str2);
char		*ft_wstrdup(const char *src);
char		*ft_wsubstr(char const *s, unsigned int start, size_t len);
int			ft_strncpy(char *dest, char *src, size_t cpy_len);
void		ft_puterror(const char *s1, const char *s2, const char *s3);
char		*ft_echo_env(char *str, t_envlist *e_list);
int			ft_wpipe(int fd[2]);
void		ft_wexecve(char *file, char **argv, char **envp);
void		ft_wsignal(int sig, void f(int));
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
int			count_env_list_size(t_envlist	*ptr);
void		free_env_list(t_envlist **env_list);
void		free_envp(char **envp);
t_envlist	*ft_findenv(const char *name);
char		*ft_getenv(char *name);
int			ft_setenv(const char *name, const char *value, int overwrite);
void		ft_unsetenv(char *unset_key);
char		*get_env_name(char *env);
char		*get_env_value(char *env);
void		init_env_list(char **envp);
t_envlist	split_env(const char *str);
void		split_and_join_env(t_envlist *new_var, const char *str);
t_redirect	*redirect_new(void);
t_redirect	*redirect_add(t_redirect **redirect_list, t_redirect *new_redirect);
void		free_redirects(t_redirect **redirect_list);
void		command_add_back(t_command *new_command);
void		free_command(t_command *cmd);
void		free_command_table(void);
t_command	*del_command(t_command *cmd);
bool		is_valid_exit_status(char	*num);
void		exit_and_free_command(int exit_status);
void		sig_handler(int signum);
void		signal_handler(int signo);
void		signal_handler_child(int signo);
void		check_execve(char *argv);
void		del_token(void *token_ptr);
bool		is_valid_var_char(const char c);
void		sig_handler(int signum);
void		signal_handler(int signo);
void		set_status_from_child_status(int wstatus);
bool		execute_built_in(t_command *cmd);
int			execute_external(t_command *cmd, char **envp);
int			heredoc(t_redirect *r, t_command *cmd);
void		realloc_heredoc(t_command *cmd, size_t new_size);
void		heredoc_add_line(t_command *cmd, char *line);
void		heredoc_insert_env(char **line, char *env, \
				size_t start, size_t end);
void		heredoc_expand_variables(char **line);
void		close_exec_fds(void);
int			process_redirect_list(t_command *cmd);
bool		is_space(char c);
bool		is_delimeter(char c);
void		init_g_data(void);
void		inits(char **envp);
int			wget_next_line(int script_fd, char **line);
int			ft_atoi_err(const char *nptr, bool *err);
#endif
