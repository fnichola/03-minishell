/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:02:55 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/11 06:55:01 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

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
		state_func_table[l->state].lex_func(l); //構造体の[]はenumでt_stateとインデックスが紐づいている。
		if (l->found_token)//もうトークンが分かった時点でfound_tokenをtrueにしてあげる。
		{
			// debug_log("l->token_type = %u\n", l->token_type);
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
		if ((l->line)[l->i]) //tokenができてなかったら一文字進める
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
t_list	*tokenizer(const char *line)
{
	t_state_func_row		*state_func_table;
	t_token					*new_token;
	t_list					*token_list;
	t_lex_arg				l;

	new_token = NULL;
	token_list = NULL;
	state_func_table = init_state_func_table();//stateと関数ポインタを作成している。
	init_lex_arg(&l, line); //lineは不要。ここで関数ポインタに渡すための引数を定義
	new_token = get_next_token(&l, state_func_table);
	while (new_token)
	{
		// debug_log("word = %s\n", new_token->word);
		ft_lstadd_back(&token_list, ft_lstnew(new_token));
		// debug_log("new_token->word %s\n", (char *)token_list->next->content);
		new_token = get_next_token(&l, state_func_table);
	}
	free(state_func_table);
	return (token_list);
}

//int	main()
//{
//	char	*line;
//	t_list	*token_list;
//	t_list	*list_ptr;
//
//	line = readline("lexer-test$ ");
//	token_list = tokenizer(line);
//	list_ptr = token_list;
//	debug_log(
//	"\n\n"
//	"---------------------------\n"
//	"Line:\n"
//	"---------------------------\n"
//	"%s\n", line
//	);
//	debug_log(
//		"\n\n"
//		"---------------------------\n"
//		"Token List:\n"
//		"---------------------------\n"
//		);
//	while (token_list)	
//	{
//		debug_log("<%s> \"%s\"\n", 
//			token_type_to_str(((t_token *)token_list->content)->token_type), 
//			((t_token *)token_list->content)->word);
//		token_list = token_list->next;
//	}
//	ft_lstclear(&list_ptr, del_token);
//	free(line);
//	return (0);
//}
