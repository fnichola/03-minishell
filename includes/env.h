/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:35:29 by akihito           #+#    #+#             */
/*   Updated: 2022/07/06 15:20:33 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../libft/libft.h"
# include "minishell.h"

typedef struct s_envlist { //環境変数を格納する構造体　単方向線形リスト（順番の入れ替えはないから）
	char				*key; //環境変数の名前
	char				*value;//環境変数の値（書き換わる）（書き換えられたものが元の環境変数に戻るときはどうする？）
	struct s_envlist	*next;
}	t_envlist;

t_envlist			*init_env_list(char **envp);
// char				**get_env_key(char *evn);
t_envlist			*create_env_list(char *envp, t_envlist *node);
char				*get_env_key(char *env);
char				*get_env_value(char *env);
# endif 