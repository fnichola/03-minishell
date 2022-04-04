/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function-lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:02:55 by fnichola          #+#    #+#             */
/*   Updated: 2022/04/04 20:57:32 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

// void	slice_new_token(t_lex_arg *l, size_t length, t_token_type token_type)
// {
// 	size_t	i;
// 	size_t	j;
// 	t_token	*token;

// 	i = l->start_index;
// 	j = 0;
// 	token = malloc(sizeof(t_token));
// 	if (!token)
// 		exit(1);
// 	token->word = malloc_error_check(sizeof(char) * (length + 1));
// 	while (j < length)
// 	{
// 		token->word[j] = l->line[i];
// 		i++;
// 		j++;
// 	}
// 	token->word[j] = 0;
// 	token->token_type = token_type;
// 	ft_lstadd_back(&(l->token_list), ft_lstnew(token));
// 	return ;
// }

/**
 * Returns the next token from the string "line".
 * e.g.
 * <T_WORD> "ls"
 */
t_token	*get_next_token(t_lex_arg *l, const t_state_func_row *state_func_table)
{
	t_token	*token;

	token = malloc_error_check(sizeof(t_token));
	l->state = NEUTRAL;
	l->start_index = l->i;
	while (1)
	{
		state_func_table[l->state].lex_func(l);
		if (l->state == RETURN_TOKEN)//もうトークンが分かった時点でstateをRETURN_TOKENにしてあげる。
		{
			printf("[RETURN_TOKEN]\n");
			if (l->token_type == T_EOL)
				return (NULL);
			token->word = ft_substr(l->line, l->start_index, (l->i - l->start_index));
			token->token_type = l->token_type;
			return (token);
		}
		(l->i)++;
	}
	return (NULL);
}

/**
 * Returns a list of tokens.
 * e.g.:
 * <T_WORD>	"ls"
 * <T_WORD>	"dir"
 * <T_PIPE>	"|"
 * <T_WORD>	"grep"
 * <T_WORD> "something"
 */
t_list	*tokenizer(char *line)
{
	const t_state_func_row	*state_func_table;
	t_token					*new_token;
	t_list					*token_list;
	t_lex_arg 				l;

	new_token = NULL;
	token_list = NULL;
	state_func_table = init_state_func_table(); // need free_state_func_table too
	// *(l->i) = 0;
	init_lex_arg(&l, line); //lineを削除します。
	new_token = get_next_token(&l, state_func_table);
	while (new_token)
	{
		printf("<%s> \"%s\"\n", token_type_to_str(new_token->token_type), new_token->word);
		// ft_lstadd_back(&token_list, ft_lstnew(new_token));
		new_token = get_next_token(&l, state_func_table);
	}
	return (token_list);
}

int	main()
{
	char	*line = "ls dir | grep something > file.txt"; // for initial testing, let's use this instead of readline
	// t_list	*token_list;
	// t_list	*list_ptr;

	// line = readline("lexer-test$ "); // no readline for simple testing
	// token_list = tokenizer(line);
	// list_ptr = token_list;
	// while (token_list)	
	// {
	// 	printf("<%s> \"%s\"\n", 
	// 		token_type_to_str(((t_token *)token_list->content)->token_type), 
	// 		((t_token *)token_list->content)->word);
	// 	token_list = token_list->next;
	// }
	// ft_lstclear(&list_ptr, del_token);
	// free(line);
	tokenizer(line);
	return (0);
}
