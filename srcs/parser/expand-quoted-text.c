/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand-quoted-text.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:26:16 by fnichola          #+#    #+#             */
/*   Updated: 2022/08/18 16:28:25 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static bool	is_valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	else
		return (false);
}

static void	expand_and_join(t_parse_arg *p, char *pre_str,
						char *quoted_var, char *post_str)
{
	char	*found_env;
	char	*tmp_str;
	char	*joined_str;
	size_t	env_length;

	env_length = ft_strlen(quoted_var);
	found_env = ft_findenv(p->e_list, quoted_var);//見つからなかったらNULLを返す
	if (found_env)
	{
		tmp_str = ft_strjoin(pre_str, found_env);
		joined_str = ft_strjoin(tmp_str, post_str);
		free(tmp_str);
	}
	else
	{
		joined_str = ft_strjoin(pre_str, post_str);
	}
	free(p->token->word);
	p->token->word = joined_str;
}

static void	split_quoted_text(t_parse_arg *p, size_t i)
{
	size_t	start_index;
	char	*quoted_var;
	char	*pre_str;
	char	*post_str;

	pre_str = ft_substr(p->token->word, 0, i);
	i++;
	start_index = i;
	while (p->token->word[i] && is_valid_var_char(p->token->word[i]))
		i++;
	quoted_var = ft_substr(p->token->word, start_index, i - start_index);// echo "$HOME!"は/Users/nicでOK
	post_str = ft_substr(p->token->word, i, ft_strlen(p->token->word) - i);
	expand_and_join(p, pre_str, quoted_var, post_str);
	free(pre_str);
	free(post_str);
	free(quoted_var);
}

void	expand_quoted_text(t_parse_arg *p)
{
	char	*tmp_str;
	size_t	i;

	i = 0;
	while (p->token->word[i])
	{
		if (p->token->word[i] == '$')
		{
			split_quoted_text(p, i);
			i = 0;
		}
		if (p->token->word[i])
			i++;
	}
}