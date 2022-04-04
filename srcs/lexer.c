/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:39:20 by fnichola          #+#    #+#             */
/*   Updated: 2022/03/30 01:26:55 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_delimeter(char c)
{
	if ((c >= '\t' && c <= '\r')
		|| c == ' '
		|| c == '|'
		|| c == '<'
		|| c == '>')
		return (true);
	return (false);
}
 

t_token	*slice_new_token( char *line, size_t start_index, size_t length, t_token_type token_type)
{
	size_t	i;
	size_t	j;
	t_token	*token;

	i = start_index;
	j = 0;
	token = malloc(sizeof(t_token));
	printf("length=%zu\n", length);
	if (!token)
	{
		exit(1);
	}
	token->word = malloc(sizeof(char) * (length + 1)); //add error handling
	if (!token->word)
	{
		exit(1);
	}
	while (j < length)
	{
		token->word[j] = line[i];
		i++;
		j++;
	}
	token->word[j] = 0;
	token->token_type = token_type;
	// printf("token.word: %s\n", token.word);
	return (token);
}

t_token	*get_next_token(char *line)
{
	t_state			state;
	static size_t	i;
	size_t			start_index;

	state = NEUTRAL;
	while (state == NEUTRAL && line[i])
	{
		start_index = i;
		if (line[i] == '|')
		{
			i++;
			return (slice_new_token(line, start_index, 1, T_PIPE));
		}
		else if (line[i] == '$')
		{
			i++;
			if (!line[i] || is_delimeter(line[i]))
				return (slice_new_token(line, start_index, 1, T_WORD));
			if (line[i] == '$')
			{
				i++;
				return (slice_new_token(line, start_index, 1, T_PID));
			}
			if (line[i] == '?')
			{
				i++;
				return (slice_new_token(line, start_index, 1, T_EXIT_STATUS));
			}
			start_index = i;
			state = VARIABLE;
			break ;
		}
		else if (line[i] == '>')
		{
			i++;
			state = GTGT;
			break ;
		}
		else if (line[i] == '<')
		{
			i++;
			state = LTLT;
			break ;
		}
		else if (line[i] == '\'')
		{
			i++;
			start_index++;
			state = IN_SINGLE_QUOTE;
			break ;
		}
		else if (line[i] == '"')
		{
			i++;
			start_index++;
			state = IN_DOUBLE_QUOTE;
			break ;
		}
		else if (line[i] == ' ' || line[i] == '\t') //isspace
		{
			i++;
			continue ;
		}
		else
		{
			state = IN_WORD;
			continue ;
		}
		i++;
	}
	// while (state == VARIABLE)
	// {
	// 	if (!line[i] || is_delimeter(line[i]))
	// 		return (slice_new_token(line, start_index, i - start_index, T_VAR));
	// 	i++;
	// }
	// while (state == GTGT && line[i])
	// {
	// 	if (line[i] == '>')
	// 	{
	// 		i++;
	// 		return (slice_new_token(line, start_index, 2, T_GTGT));
	// 	}
	// 	return (slice_new_token(line, start_index, 1, T_GT));
	// }
	// while (state == LTLT && line[i])
	// {
	// 	if (line[i] == '<')
	// 	{
	// 		i++;
	// 		return (slice_new_token(line, start_index, 2, T_LTLT));
	// 	}
	// 	return (slice_new_token(line, start_index, 1, T_LT));
	// }
	// while (state == IN_SINGLE_QUOTE && line[i])
	// {
	// 	if (line[i] == '\'')
	// 	{
	// 		i++;
	// 		return (slice_new_token(line, start_index, i - start_index - 1, T_WORD));
	// 	}
	// 	i++;
	// }
	// while (state == IN_DOUBLE_QUOTE && line[i])
	// {
	// 	if (line[i] == '\"')
	// 	{
	// 		printf("ダブルクォーと\n");
	// 		i++;
	// 		return (slice_new_token(line, start_index, i - start_index - 1, T_WORD));
	// 	}
	// 	i++;
	// }
	while (state == IN_WORD && line[i])
	{
		if (line[i] == '|' ||
			line[i] == '<' ||
			line[i] == '>' ||
			line[i] == ' ' ||
			line[i] == '\t')
		{
			return (slice_new_token(line, start_index, i - start_index, T_WORD));
		}
		i++;
	}
	if (state == IN_WORD)
		return (slice_new_token(line, start_index, i - start_index, T_WORD));
	else
	{
		i = 0;
		return (NULL);
	}
}

t_list	*tokenizer(char *line)
{
	t_token	*new_token;
	t_list	*token_list;

	token_list = NULL;
	new_token = get_next_token(line);
	printf("new_token.word = %s\n", new_token->word);
	while (new_token)
	{
		ft_lstadd_back(&token_list, ft_lstnew(new_token));
		new_token = get_next_token(line);
	}
	// printf("token_list = %p, next: %p\n", token_list, token_list->next);
	return (token_list);
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
	else if (token_type == T_PID)
		return ("T_PID");
	else if (token_type == T_EXIT_STATUS)
		return ("T_EXIT_STATUS");
	else if (token_type == T_SPECIAL)
		return ("T_SPECIAL");
	else if (token_type == T_ERROR)
		return ("T_ERROR");
	else
		return ("bad type!");
}

void	del_token(void *token_ptr)
{
	t_token	*token;

	token = (t_token *)token_ptr;
	free(token->word);
	token->word = NULL;
	free(token);
	token = NULL;
}

int	main(void)
{
	char	*line;
	t_list	*token_list;
	t_list	*list_ptr;

	line = readline("lexer-test$ ");
	token_list = tokenizer(line);
	list_ptr = token_list;
	while (token_list)
	{
		printf("<%s> \"%s\"\n",
			token_type_to_str(((t_token *)token_list->content)->token_type),
			((t_token *)token_list->content)->word);
		token_list = token_list->next;
	}
	ft_lstclear(&list_ptr, del_token);
	free(line);
	return (0);
}

struct typeA array_STATE_FLOW[] = { STATE_A, EVENT_A, NEXT_A},
						{ STATE_B, EVENT_B, NEXT_B},
