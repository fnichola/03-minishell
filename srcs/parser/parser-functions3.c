/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:36:04 by akihito           #+#    #+#             */
/*   Updated: 2022/08/23 02:30:13 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void 	parser_lt(t_parse_arg *p)
{
	(void *)p;
	printf("parser_lt\n");
}

void 	parser_ltlt(t_parse_arg *p)
{
	(void *)p;
	printf("parser_ltlt\n");
}

void 	parser_file(t_parse_arg *p)
{
	// exit(1);
	p->token->token_type = T_FILE;
	// (void *)p;
	printf("parser_file\n");
	printf("next_token\n");
	printf("p->token->word %s\n", p->token->word);

	printf("p->token->token_type = %d\n", p->token->token_type);
	// exit(1);
	// if (!p->token)
	// {
		printf("!p->token\n");
		p->command->argv[p->index] = NULL;
		ft_lstadd_back(&p->command_table, ft_lstnew(p->command));
		change_state(p, ST_FINISHED);
	// }

	// p->token->token_type = T_FILE;

	// next_token(p);
	// printf("p->token->word = %d\n", p->token->token_type);
	
	// ft_dup2(open(p->command));
	// change_state(p, ST_FILE);
}