/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex-utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:28:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/20 10:35:19 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"


bool	is_delimeter(char c)
{
	if (!c
		|| c == ' '
		|| c == '\t'
		|| c == '|'
		|| c == '<'
		|| c == '>'
		)
		return (true);
	return (false);
}

bool	is_space(char c)
{
	if((c >= '\t' && c <= '\r')|| c == ' ')
		return (true);
	else
		return (false);
}

char	*token_type_to_str(t_token_type token_type)
{
	if (token_type == T_WORD)
		return ("T_WORD");
	else if (token_type == T_PIPE)
		return ("T_PIPE");
	else if (token_type == T_GT)
		return ("T_GT");
	else if (token_type == T_GTGT)
		return ("T_GTGT");
	else if (token_type == T_LT)
		return ("T_LT");
	else if (token_type == T_LTLT)
		return ("T_LTLT");
	else if (token_type == T_VAR)
		return ("T_VAR");
	else if (token_type == T_EXIT_STATUS)
		return ("T_EXIT_STATUS");
	else if (token_type == T_ERROR)
		return ("T_ERROR");
	else
		return ("bad type!");
}

void	join_substr_to_token(t_lex_arg *l)
{
	char	*tmp;
	char	*old_word;

	tmp = ft_substr(l->line, l->start_index, (l->index - l->start_index));
	old_word = l->token->word;
	if (l->token->word)
	{
		l->token->word = ft_strjoin(l->token->word, tmp);
		free(tmp);
	}
	else
		l->token->word = tmp;
	free(old_word);
	debug_log("join_substr_to_token: l->token->word=%s\n", l->token->word);
}

void	expand_var(t_lex_arg *l)
{
	char	*var_name;
	char	*found_env;
	char	*old_word;

	var_name = ft_substr(l->line, l->start_index, (l->index - l->start_index));

	found_env = ft_getenv(var_name);//見つからなかったらNULLを返す
	if (found_env)
	{
		if (l->token->word)
		{
			old_word = l->token->word;
			l->token->word = ft_strjoin(l->token->word, found_env);
			free(old_word);
		}
		else
			l->token->word = ft_strdup(found_env);
		debug_log("expand_var: var_name=%s, found_env=%s\n", var_name, found_env);
	}
	free(var_name);
	var_name = NULL;
}

void	next_char(t_lex_arg *l)
{
	if ((l->line)[l->index])
	{
		(l->index)++;
		l->current_char = (l->line)[l->index];
		debug_log("next_char: %c\n", l->current_char);
	}
	else
		debug_log("next_char: tried to go past end of line\n");
}


void	change_lex_state(t_lex_arg *l, t_state new_state)
{
	if (new_state != l->previous_state)
		l->previous_state = l->state;
	l->state = new_state;
}
