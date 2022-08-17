/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:58:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/08/17 18:38:40 by fnichola         ###   ########.fr       */
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
	if (!p->token)//
	{
		change_state(p, ST_FINISHED);
		return ;
	}
	init_command(p);
	if (p->token->token_type == T_VAR)
	{
		printf("ST_ENV\n");
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
	printf("parser_first_word\n");
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
	{
		change_state(p, ST_ENV);
	}
	else if (p->token->token_type == T_DOUBLE_QUOTED)
	{
		change_state(p, ST_IN_DQUOTE);
	}
	else if (p->token->token_type == T_PIPE)
	{
		p->command->argv[p->index] = NULL;
		ft_lstadd_back(&p->command_table, ft_lstnew(p->command));
		next_token(p);
		change_state(p, ST_NEUTRAL);
	}
	
}

bool	is_valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	else
		return (false);
}

void	parser_in_dquote (t_parse_arg *p)
{
	t_envlist	*tmp;
	char		*found_index;
	char		*found_env;
	char		*joined_str;
	printf("expand variables in double quote\n");
	//ここでexpandしてT_WORDに変更する。　

	char	*quoted_variable;
	char	*pre_str;
	char	*post_str;
	size_t	i;
	size_t	start_index;
	char	*tmp_str;

	i = 0;
	start_index = 0;
	while (p->token->word[i])
	{
		if (p->token->word[i] == '$')
		{
			pre_str = ft_substr(p->token->word, 0, i); // malloc!
			printf("pre_str: %s\n", pre_str);
			i++;
			start_index = i;
			while (p->token->word[i] && is_valid_var_char(p->token->word[i]))
			{
				i++;
			}
			quoted_variable = ft_substr(p->token->word, start_index, i - start_index);// echo "$HOME!"は/Users/nicでOK
			post_str = ft_substr(p->token->word, i, ft_strlen(p->token->word) - i);
			printf("post_str: %s\n", post_str);
			found_env = ft_findenv(p->e_list, quoted_variable);//見つからなかったらNULLを返す
			free(quoted_variable);
			printf("found_env %s\n", found_env);
			if (found_env)
			{
				tmp_str = ft_strjoin(pre_str, found_env); // malloc!
				joined_str = ft_strjoin(tmp_str, post_str); // malloc!
				free(tmp_str);
				free(p->token->word);
				p->token->word = joined_str;
				i = start_index + ft_strlen(found_env) - 1;//i = 0でもいいが、こっちの方が最適
			}
			free(pre_str);
			free(post_str);
		}
		if (p->token->word[i])
			i++;
	}
	p->token->token_type = T_WORD;
	printf("previous_state = %d\n", p->previous_state);
	change_state(p, p->previous_state);
}

// char	*ft_find_doller(t_parse_arg *p)
// {
// 	size_t	i;

// 	i = 0;
// 	// while (i < ft_strlen(p->))
// }


void	parser_env (t_parse_arg *p)
{
	// (void)p;
	char	*found_env;

	found_env = ft_findenv(p->e_list, p->token->word);//見つからなかったらNULLを返す
	printf("found_env %s\n", found_env);
	printf("p->state %d\n", p->state);
	printf("p->token->word %s\n", p->token->word);
	p->token->token_type = T_WORD;
	free(p->token->word);
	p->token->word = ft_strdup(found_env); // ft_findenv doesn't return a "free"-able string

	change_state(p, p->previous_state);
}

void	expand_env(t_parse_arg *p)
{
	(void)p;
	return ;
}
