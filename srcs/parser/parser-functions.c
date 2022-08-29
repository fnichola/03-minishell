/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:58:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/08/18 17:18:36 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	next_token(t_parse_arg *p)
{
	p->list_ptr = p->list_ptr->next;
	p->previous_token = p->token;
	if (p->list_ptr)
		p->token = (t_token *)p->list_ptr->content;
	else
		p->token = NULL;
}

void	change_state(t_parse_arg *p, t_state new_state)
{
	p->previous_state = p->state;
	p->state = new_state;
}

void	init_command(t_parse_arg *p)
{
	p->index = 0;
	p->command = malloc_error_check(sizeof(t_command));
	p->command->argv = malloc_error_check(sizeof(char *) * 32); // 32 is max length of a single command, this should be changed!
	p->command->output_file = NULL;
	p->command->input_file = NULL;
	p->command->error_file = NULL;
	p->command->argv[p->index] = NULL;
}

void	parser_neutral(t_parse_arg *p)
{
	if (!p->token)
	{
		change_state(p, ST_FINISHED);
		return ;
	}
	init_command(p);
	if (p->token->token_type == T_VAR)
	{
		change_state(p, ST_ENV);
	}
	if (p->token->token_type == T_DOUBLE_QUOTED)
	{
		change_state(p, ST_IN_DQUOTE);
	}
	if (p->token->token_type == T_WORD)
	{
		change_state(p, ST_FIRST_WORD);
	}
	else if (p->token->token_type == T_PIPE)
		next_token(p);
}

void	parser_first_word(t_parse_arg *p)
{
	next_token(p);
	p->command->argv[p->index] = ft_strdup(p->previous_token->word); // duplicate token string so we can free all tokens later
	(p->index)++;
	change_state(p, ST_SIMPLE_COMMAND);
}

void	parser_simple_command(t_parse_arg *p)
{
	if (!p->token)
	{
		p->command->argv[p->index] = NULL;
		ft_lstadd_back(&p->command_table, ft_lstnew(p->command));
		change_state(p, ST_FINISHED);
	}
	else if (p->token->token_type == T_WORD)
	{
		p->command->argv[p->index] = ft_strdup(p->token->word);
		p->token = NULL;
		(p->index)++;
		next_token(p);
	}
	else if (p->token->token_type == T_VAR)
		change_state(p, ST_ENV);
	else if (p->token->token_type == T_DOUBLE_QUOTED)
		change_state(p, ST_IN_DQUOTE);
	else if (p->token->token_type == T_PIPE)
	{
		p->command->argv[p->index] = NULL;
		ft_lstadd_back(&p->command_table, ft_lstnew(p->command));
		next_token(p);
		change_state(p, ST_NEUTRAL);
	}
}

//ここでexpandしてT_WORDに変更する。　
void	parser_in_dquote(t_parse_arg *p)
{
	t_envlist	*tmp;
	char		*found_index;
	char		*found_env;
	char		*joined_str;

	expand_quoted_text(p);
	p->token->token_type = T_WORD;
	change_state(p, p->previous_state);
}

void	parser_env(t_parse_arg *p)
{
	char	*found_env;

	found_env = ft_getenv(p->token->word);//見つからなかったらNULLを返す
	if (found_env)
	{
		p->token->token_type = T_WORD;
		free(p->token->word);
		p->token->word = ft_strdup(found_env); // ft_findenv doesn't return a "free"-able string
	}
	else
		next_token(p); // if no env is found, skip this token
	change_state(p, p->previous_state);
}
