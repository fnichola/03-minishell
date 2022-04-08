/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:02:55 by fnichola          #+#    #+#             */
/*   Updated: 2022/04/08 23:27:25 by atomizaw         ###   ########.fr       */
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

	l->state = ST_NEUTRAL;
	l->start_index = l->i;
	while (1)
	{
		printf("\nindex: %zu, character: '%c'\n", l->i, (l->line)[l->i]);
		state_func_table[l->state].lex_func(l);//構造体の[]はenumでt_stateとインデックスが紐づいている。
		if (l->found_token)//もうトークンが分かった時点でfound_tokenをtrueにしてあげる。
		{
			printf("[found_token == true]\n");
			if (l->token_type == T_EOL)
				return (NULL);
			token = malloc_error_check(sizeof(t_token));
			token->word = ft_substr(l->line, l->start_index, (l->i - l->start_index));
			token->token_type = l->token_type;
			if (l->state == ST_IN_DOUBLE_QUOTE || l->state == ST_IN_SINGLE_QUOTE)
				(l->i)++;
			l->found_token = false;
			return (token);
		}
		if ((l->line)[l->i])//tokenができてなかったら一文字進める
			(l->i)++;
	}
	return (NULL);
}

/**
 * Returns a list of all tokens in the string "line".
 * e.g.:
 * <T_WORD>	"ls"
 * <T_WORD>	"dir"
 * <T_PIPE>	"|"
 * <T_WORD>	"grep"
 * <T_WORD> "something"
 */
t_list	*tokenizer(char *line)
{
	printf(
		"---------------------------\n"
		"Tokenizer:\n"
		"---------------------------\n"
		);
	t_state_func_row		*state_func_table;
	t_token					*new_token;
	t_list					*token_list;
	t_lex_arg 				l;

	new_token = NULL;
	token_list = NULL;
	state_func_table = init_state_func_table();//stateと関数ポインタを作成している。
	init_lex_arg(&l, line); //lineは不要。ここで関数ポインタに渡すための引数を定義
	new_token = get_next_token(&l, state_func_table);
	while (new_token)
	{
		printf("<%s> \"%s\"\n", token_type_to_str(new_token->token_type), new_token->word);
		ft_lstadd_back(&token_list, ft_lstnew(new_token));
		new_token = get_next_token(&l, state_func_table);
	}
	free(state_func_table);
	return (token_list);
}

int	main()
{
	char	*line;
	t_list	*token_list;
	t_list	*list_ptr;

	line = readline("lexer-test$ ");
	token_list = tokenizer(line);
	list_ptr = token_list;
	printf(
	"\n\n"
	"---------------------------\n"
	"Line:\n"
	"---------------------------\n"
	"%s\n", line
	);
	printf(
		"\n\n"
		"---------------------------\n"
		"Token List:\n"
		"---------------------------\n"
		);
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
