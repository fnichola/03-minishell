/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:58:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 15:29:32 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	parser_start_word(t_parse_arg *p)
{
	p->command->argv[p->index] = ft_strdup(p->token->word);
	next_token(p);
	(p->index)++;
	change_state(p, ST_SIMPLE_COMMAND);
}

void	parser_simple_command(t_parse_arg *p)
{
	if (!p->token)
	{
		p->command->argv[p->index] = NULL;
		command_add_back(p->command);
		change_state(p, ST_FINISHED);
	}
	else if (p->token->type == T_WORD)
	{
		p->command->argv[p->index] = ft_strdup(p->token->word);
		p->token = NULL;
		(p->index)++;
		next_token(p);
	}
	else if (p->token->type == T_PIPE)
	{
		p->command->argv[p->index] = NULL;
		command_add_back(p->command);
		next_token(p);
		change_state(p, ST_NEUTRAL);
	}
	else if (is_redirect_token(p->token->type))
		change_state(p, ST_REDIRECT);
}

void	parser_in_dquote(t_parse_arg *p)
{
	expand_quoted_text(p);
	p->token->type = T_WORD;
	change_state(p, p->previous_state);
}

void	parser_env(t_parse_arg *p)
{
	char	*found_env;

	found_env = ft_getenv(p->token->word);
	if (found_env)
	{
		p->token->type = T_WORD;
		free(p->token->word);
		p->token->word = ft_strdup(found_env);
	}
	else
		next_token(p);
	change_state(p, p->previous_state);
}

void	parser_redirect(t_parse_arg *p)
{
	t_redirect		*new_redirect;

	new_redirect = redirect_new();
	if (p->token->type == T_GT || p->token->type == T_GTGT)
	{
		new_redirect->type = OUTPUT_REDIRECT;
		new_redirect->append = p->token->type == T_GTGT;
		next_token(p);
		if (p->token && p->token->type == T_WORD)
			new_redirect->filename = ft_strdup(p->token->word);
	}
	else if (p->token->type == T_LT || p->token->type == T_LTLT)
	{
		new_redirect->type = INPUT_REDIRECT;
		new_redirect->append = p->token->type == T_LTLT;
		next_token(p);
		if (p->token && p->token->type == T_WORD)
			new_redirect->filename = ft_strdup(p->token->word);
	}
	redirect_add(&p->command->redirects, new_redirect);
	next_token(p);
	change_state(p, ST_SIMPLE_COMMAND);
}
