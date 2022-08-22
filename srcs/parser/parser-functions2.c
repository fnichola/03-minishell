/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:26:18 by akihito           #+#    #+#             */
/*   Updated: 2022/08/23 01:52:49 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	parser_simple_command(t_parse_arg *p)
{
	printf("simple command\n");
	// printf("p->token->token_type %d\n", p->token->token_type);
	if (!p->token)
	{
		printf("!p->token\n");
		p->command->argv[p->index] = NULL;
		ft_lstadd_back(&p->command_table, ft_lstnew(p->command));
		change_state(p, ST_FINISHED);
	}
	else if (p->token->token_type == T_WORD)
	{
		printf("p->token->token_type\n");
		p->command->argv[p->index] = ft_strdup(p->token->word);
		p->token = NULL;//なぜ??
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
	else if (p->token->token_type == T_GT)
	{
		printf("p->token->token_type == GT\n");
		p->command->argv[p->index] = NULL;
		ft_lstadd_back(&p->command_table, ft_lstnew(p->command));
		next_token(p);
		change_state(p, ST_FILE);
	}
	// else if (p->token->token_type == T_GTGT)
	// {
	// 	printf("p->token->token_type == GTGT\n");
	// 	p->command->argv[p->index] = NULL;
	// 	ft_lstadd_back(&p->command_table, ft_lstnew(p->command));
	// 	next_token(p);
	// 	change_state(p, ST_GTGT);
	// }
	printf("end\n");
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

	found_env = ft_findenv(p->e_list, p->token->word);//見つからなかったらNULLを返す
	p->token->token_type = T_WORD;
	free(p->token->word);
	p->token->word = ft_strdup(found_env); // ft_findenv doesn't return a "free"-able string
	change_state(p, p->previous_state);
}

void	parser_gt(t_parse_arg *p)
{
	(void *)p;
	printf("parser_gt\n");
	// printf("p->token->token_type = %d\n", p->token->token_type);
	p->token->token_type = T_GT;
	set_redirect(p);
	change_state(p, ST_FILE);
	next_token(p);
}

void	parser_gtgt(t_parse_arg *p)
{
	(void *)p;
	printf("parser_gtgt\n");
	p->token->token_type = T_WORD;
	// next_token(p);
	change_state(p, ST_GTGT);
}

void set_redirect(t_parse_arg *p)
{
	(void *)p;

	printf("set_redirect\n");
	printf("p->token->word = %d\n", p->token->token_type);
	
}