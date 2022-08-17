/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:58:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/08/17 11:18:23 by akihito          ###   ########.fr       */
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
	if (!p->token)//
	{
		p->state = ST_FINISHED;
		return ;
	}
	init_command(p);
	if (p->token->token_type == T_VAR)
	{
		p->state = ST_ENV;
	}
	if (p->token->token_type == T_DOUBLE_QUOTE)
	{
		p->state = ST_IN_DQUOTE;
	}
	if (p->token->token_type == T_WORD)
	{
		p->state = ST_FIRST_WORD;
	}
	else if (p->token->token_type == T_PIPE)
		next_token(p);
}

void	parser_first_word(t_parse_arg *p)
{
	next_token(p);
	p->command->argv[p->index] = ft_strdup(p->previous_token->word); // duplicate token string so we can free all tokens later
	(p->index)++;
	p->state = ST_SIMPLE_COMMAND;
}

void	parser_simple_command(t_parse_arg *p)
{
	if (!p->token)
	{
		p->command->argv[p->index] = NULL;
		ft_lstadd_back(&p->command_table, ft_lstnew(p->command));
		p->state = ST_FINISHED;
	}
	else if (p->token->token_type == T_WORD)
	{
		p->command->argv[p->index] = ft_strdup(p->token->word);
		p->token = NULL;
		(p->index)++;
		next_token(p);
	}
	else if (p->token->token_type == T_PIPE)
	{
		p->command->argv[p->index] = NULL;
		ft_lstadd_back(&p->command_table, ft_lstnew(p->command));
		next_token(p);
		p->state = ST_NEUTRAL;
	}
}

void	expand_env(t_parse_arg *p)
{
	(void)p;
	return ;
}
