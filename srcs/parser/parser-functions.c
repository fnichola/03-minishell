/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:58:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 15:28:37 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	next_token(t_parse_arg *p)
{
	if (p->list_ptr)
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
	p->command->argv = malloc_error_check(sizeof(char *) * 32);
	p->command->argv[p->index] = NULL;
	p->command->redirects = NULL;
	p->command->heredoc = NULL;
	p->command->pid = 0;
	p->command->input_fd = STDIN_FILENO;
	p->command->output_fd = STDOUT_FILENO;
	p->command->prev = NULL;
	p->command->next = NULL;
}

bool	is_redirect_token(t_token_type t)
{
	if (t == T_GT || \
		t == T_GTGT || \
		t == T_LT || \
		t == T_LTLT)
		return (true);
	return (false);
}

void	parser_neutral(t_parse_arg *p)
{
	if (!p->token)
	{
		change_state(p, ST_FINISHED);
		return ;
	}
	init_command(p);
	change_state(p, ST_SIMPLE_COMMAND);
}
