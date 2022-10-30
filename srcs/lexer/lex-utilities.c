/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex-utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:28:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 16:46:00 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	join_str_to_token(t_lex_arg *l, char *str)
{
	char	*old_word;

	old_word = l->token->word;
	if (l->token->word)
	{
		l->token->word = ft_strjoin(l->token->word, str);
		free(str);
	}
	else
		l->token->word = str;
	free(old_word);
}

void	flush_to_token(t_lex_arg *l)
{
	char	*tmp;

	if (l->start_index == l->index)
		return ;
	tmp = ft_substr(l->line, l->start_index, (l->index - l->start_index));
	if (tmp)
		join_str_to_token(l, tmp);
}

void	expand_var(t_lex_arg *l)
{
	char	*var_name;
	char	*found_env;

	if (l->current_char == '?')
	{
		join_str_to_token(l, ft_itoa(g_data.exit_status));
		next_char(l);
		l->start_index = l->index;
	}
	else
	{
		l->start_index = l->index;
		while (ft_isalnum(l->current_char))
			next_char(l);
		var_name = ft_substr(l->line, l->start_index,
				(l->index - l->start_index));
		l->start_index = l->index;
		found_env = ft_getenv(var_name);
		if (found_env)
			join_str_to_token(l, ft_wstrdup(found_env));
		free(var_name);
	}
}

void	next_char(t_lex_arg *l)
{
	if ((l->line)[l->index])
	{
		(l->index)++;
		l->current_char = (l->line)[l->index];
		if (l->current_char)
			l->next_char = (l->line)[l->index + 1];
	}
}

void	change_lex_state(t_lex_arg *l, t_state new_state)
{
	if (new_state != l->previous_state)
		l->previous_state = l->state;
	l->state = new_state;
}
