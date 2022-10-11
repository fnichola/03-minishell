/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:35:29 by akihito           #+#    #+#             */
/*   Updated: 2022/09/26 03:31:54 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../libft/libft.h"
# include "minishell.h"
# include <stdbool.h>

typedef struct s_envlist {
	char				*name; //環境変数の名前
	char				*value; //環境変数の値（書き換わる）（書き換えられたものが元の環境変数に戻るときはどうする？）
	char				*string; // 'env' formatted string (i.e. "NAME=VALUE")
	bool				export; // 子プロセスに渡すか渡さないか
	struct s_envlist	*prev;
	struct s_envlist	*next;
}	t_envlist;

void		init_env_list(char **envp);
t_envlist	*create_env_list(char *envp, t_envlist *node);
char		*get_env_name(char *env);
char		*get_env_value(char *env);
int			ft_setenv(const char *name, const char *value, int overwrite);
char		*ft_getenv(char *name);
t_envlist	*env_list_add_back(t_envlist **env_list, t_envlist *new_node);
void		free_env_list(t_envlist **env_list);
t_envlist	*env_list_sort(t_envlist *env_list);
t_envlist	*env_list_first(t_envlist *ptr);
t_envlist	*env_list_last(t_envlist *ptr);
char		**export_to_envp(void);
void		free_envp(char **envp);
char		*env_to_string(const char *name, const char *value);
t_envlist 	*env_list_copy_all(t_envlist *node);
t_envlist	*env_list_new(char *name, char *value, char *string);
# endif 
