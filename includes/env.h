/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 22:35:29 by akihito           #+#    #+#             */
/*   Updated: 2022/10/30 11:03:44 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_envlist {
	char				*name;
	char				*value;
	char				*string;
	bool				export;
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
t_envlist	*env_list_copy_all(t_envlist *node);
t_envlist	*env_list_new(char *name, char *value, char *string);

#endif 
