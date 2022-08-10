/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:49:22 by akihito           #+#    #+#             */
/*   Updated: 2022/08/10 20:02:19 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

char	*ft_echo_env(char *str, t_envlist *e_list)
{
	char		*tmp;
	size_t		i;
	t_envlist	*e_node;
	char		*after_doll;
	char		*ans;

	e_node = e_list->next;
	i = 0;
	after_doll = NULL;
	//まず$を探してそのインデックスをwsubstrの第二引数に渡す
	if (str)
		after_doll = ft_strchr(str, '$');
	printf("after_doll = %s\n", after_doll);
	if (after_doll)//$があった時
	{
		ans = find_doll_env(e_list, after_doll);//
		while (i < ft_strlen(after_doll))
		{
			tmp = ft_wsubstr(after_doll, 0, i);
			printf("tmp = %s\n", tmp);
			// while (e_node)
			// {
			ans = ft_findenv(e_list, tmp);
			// }
			i++;
		}
		if (!ans)//$があったがシェル変数は見つからなかった時の処理。$と右隣の1文字を消した文字列を返す。2文字しなかった場合は空文字列を返す
			ans = ft_wsubstr(str, 2, ft_strlen(str) - 1);
	}
	else
	{
		printf("else\n");
		ans = str;
	}
	return (ans);

}

char	*find_doll_env(t_envlist *e_list, char *after_doll)
{
	char		*tmp;
	size_t		i;
	char		*ans;
	t_envlist	*e_node;

	i = 0;
	ans = NULL;
	e_node = e_list->next;
	printf("find_doll_env\n");
	while (i < ft_strlen(after_doll))
	{
		while (e_node)
		{
			tmp = ft_wsubstr(after_doll, 0, i);
			if (ft_findenv(e_list, tmp))
				ans = ft_findenv(e_list, tmp);
			e_node = e_node->next;
		}
		i++;
	}
	return (ans);
}
