/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser-functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:58:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/29 09:33:37 by fnichola         ###   ########.fr       */
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
	const char *state_strs[8] = {
		"ST_NEUTRAL",
		"ST_START_WORD",
		"ST_SIMPLE_COMMAND",
		"ST_REDIRECT",
		"ST_ENV",
		"ST_IN_DQUOTE",
		"ST_FINISHED",
		NULL
	};
	debug_log("change_state: changing to %s\n", state_strs[new_state]);
	p->previous_state = p->state;
	p->state = new_state;
}

void	init_command(t_parse_arg *p)
{
	p->index = 0;
	p->command = malloc_error_check(sizeof(t_command));
	p->command->argv = malloc_error_check(sizeof(char *) * 32); // 32 is max length of a single command, this should be changed!
	p->command->argv[p->index] = NULL;
	p->command->redirects = NULL;
	p->command->heredoc = NULL;
	p->command->pid = 0;
	p->command->input_fd = STDIN_FILENO;
	p->command->output_fd = STDOUT_FILENO;
	p->command->prev = NULL;
	p->command->next = NULL;
}

bool is_redirect_token(t_token_type t)
{
	if (t == T_GT ||
		t == T_GTGT ||
		t == T_LT ||
		t == T_LTLT)
		return (true);
	return (false);
}

void	parser_neutral(t_parse_arg *p)
{
	if (!p->token)
	{
		debug_log("g_data.exit_status %d\n", g_data.exit_status);
		change_state(p, ST_FINISHED);
		return ;
	}
	debug_log("parser_neutral: p->token->word = %s\n", p->token->word);
	init_command(p);
	change_state(p, ST_SIMPLE_COMMAND);
	// else if (p->token->type == T_PIPE)
	// 	next_token(p);
	// else if (is_redirect_token(p->token->type))
	// 	change_state(p, ST_REDIRECT);
}

void	parser_start_word(t_parse_arg *p)
{
	p->command->argv[p->index] = ft_strdup(p->token->word); // duplicate token string so we can free all tokens later
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

//ここでexpandしてT_WORDに変更する。　
void	parser_in_dquote(t_parse_arg *p)
{
	expand_quoted_text(p);
	p->token->type = T_WORD;
	change_state(p, p->previous_state);
}

void	parser_env(t_parse_arg *p)
{
	char	*found_env;

	found_env = ft_getenv(p->token->word);//見つからなかったらNULLを返す
	if (found_env)
	{
		p->token->type = T_WORD;
		free(p->token->word);
		p->token->word = ft_strdup(found_env); // ft_findenv doesn't return a "free"-able string
	}
	else
		next_token(p); // if no env is found, skip this token
	change_state(p, p->previous_state);
}

void	parser_redirect(t_parse_arg *p)// > と >>で入れる
{
	t_redirect		*new_redirect;

	new_redirect = redirect_new();
	if (p->token->type == T_GT || p->token->type == T_GTGT)
	{
		new_redirect->type = OUTPUT_REDIRECT;
		new_redirect->append = p->token->type == T_GTGT;
		next_token(p);
		if (p->token && p->token->type == T_WORD)
		{
			new_redirect->filename = ft_strdup(p->token->word);
			debug_log("parser_redirect: setting output redirect to %s, append=%d\n", p->token->word, new_redirect->append);
		}
	}
	else if (p->token->type == T_LT || p->token->type == T_LTLT)
	{
		new_redirect->type = INPUT_REDIRECT;
		new_redirect->append = p->token->type == T_LTLT;
		next_token(p);
		if (p->token && p->token->type == T_WORD)
		{
			debug_log("parser_redirect: setting input redirect to %s, append=%d\n", p->token->word, new_redirect->append);
			new_redirect->filename = ft_strdup(p->token->word);
		}
	}
	redirect_add(&p->command->redirects, new_redirect);
	next_token(p);
	change_state(p, ST_SIMPLE_COMMAND);
}

// void	set_redirect(t_parse_arg *p, int fd)
// {
// 	t_redirect	*tmp;

// 	tmp = (t_redirect *)malloc(sizeof(g_data.redirect));
// 	tmp->count_cmds = p->count_cmds;//先にインクリメントしてしまっているので、
// 	tmp->fd = fd;
// 	tmp->redirect_type = 0;
// 	tmp->next = NULL;
// 	return ;
// }

// int	add_list(int value, size_t count_cmds, t_redirect *nil)
// {
// 	t_redirect	*node;
// 	t_redirect	*prev;

// 	// if (is_duplicated(nil, value))
// 		// ft_error();
// 	prev = nil->prev;
// 	node = (t_redirect *)malloc(sizeof(t_redirect));
// 	if (!node)
// 		exit(1);
// 	node = nil;
// 	while (node->next != nil)
// 		node = node->next;
// 	node->fd = value;
// 	nil->prev = node;
// 	prev->next = node;
// 	node->count_cmds = count_cmds;
// 	node->fd = value;
// 	node->next = nil;
// 	node->prev = prev;
// 	return (0);
// }
