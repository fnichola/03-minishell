/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:35:29 by akihito           #+#    #+#             */
/*   Updated: 2022/08/29 07:35:23 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../libft/libft.h"
# include "minishell.h"

typedef struct s_envlist {
	char				*name; //環境変数の名前
	char				*value; //環境変数の値（書き換わる）（書き換えられたものが元の環境変数に戻るときはどうする？）
	struct s_envlist	*prev;
	struct s_envlist	*next;
}	t_envlist;

void		init_env_list(char **envp);
t_envlist	*create_env_list(char *envp, t_envlist *node);
char		*get_env_key(char *env);
char		*get_env_value(char *env);
int			ft_setenv(const char *name, const char *value, int overwrite);
char		*ft_getenv(char *name);
void		*env_list_add_back(char *name, char *value);
void		free_env_list(void);
void		env_list_sort(void);
t_envlist	*env_list_first(t_envlist *ptr);
t_envlist	*env_list_last(t_envlist *ptr);
# endif 
