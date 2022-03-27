/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function-lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:02:55 by fnichola          #+#    #+#             */
/*   Updated: 2022/03/23 18:110:12 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	slice_new_token(t_lex_arg *l, size_t length, t_token_type token_type)
{
	size_t	i;
	size_t	j;
	t_token	*token;

	i = l->start_index;
	j = 0;
	token = malloc(sizeof(t_token));
	if (!token)
		exit(1);
	token->word = malloc_error_check(sizeof(char) * (length + 1));
	while (j < length)
	{
		token->word[j] = l->line[i];
		i++;
		j++;
	}
	token->word[j] = 0;
	token->token_type = token_type;
	ft_lstadd_back(&(l->token_list), ft_lstnew(token));
	return ;
}

// void	lex_netural(t_lex_arg *l)
// {
// 	*(l->i) = 0;
// 	if (l->line[*(l->i)] == '|')
// 	{
// 		(l->i)++;
// 		slice_new_token(l, 1, T_PIPE);
// 	}
// 	else if (l->line[*(l->i)]) == '$')
// 	{
// 		(l->i)++;
// 		if ()
// 	}
// }
void	del_token(void *token_ptr)
{
	t_token	*token;

	token = (t_token *)token_ptr;
	free(token->word);
	token->word = NULL;
	free(token);
	token = NULL;
}

void	lex_ltlt(t_lex_arg *l)
{
	if (l->line[*(l->i)] == '<')
	{
		(l->i)++;
		slice_new_token(l, 2, T_LTLT);
	}
	slice_new_token(l, 1, T_LT);
	return ;
}
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

void	lex_variable(t_lex_arg *l)
{
	if (!l->line[*(l->i)] || is_delimeter(l->line[*(l->i)]))
		slice_new_token(l, *(l->i) - (l->start_index), T_VAR);
	else
		(l->i)++;
	return ;
}

void	lex_gtgt(t_lex_arg *l)
{
	if (l->line[*(l->i)] == '>')
	{
		(l->i)++;
		slice_new_token(l, 2, T_GTGT);
	}
	else
		slice_new_token(l, 2, T_GTGT);
	(l->i)++;
	return ;
}

void	lex_single_quote(t_lex_arg *l)
{
	if (l->line[*(l->i)] == '\'')
	{
		(l->i)++;
		slice_new_token(l, *(l->i) - (l->start_index) - 1, T_WORD);
	}
	(l->i)++;
}

void	lex_double_quote(t_lex_arg *l)
{
	if (l->line[*(l->i)] == '\"')
	{
		(l->i)++;
		slice_new_token(l, *(l->i) - (l->start_index) - 1, T_WORD);
	}
	(l->i)++;
}


void	find_match_state(char *line, t_state_func_row *state_func_table)
{
	size_t	i;
	size_t	j;

	i = 0;
	// j = 1;
	while (line[i] != '\0')
	{
		j = 0;
		while (j < 5)
		{
			if (line[i] == state_func_table[j].symbol)
			{
				state_func_table[j].lex_func;
			}
		}


	}
}

void	init_lex_arg(t_lex_arg *l, char *line)
{
	l->line = line;
	l->i = 0;
	l->start_index = 0;
	l->state = NEUTRAL;
	l->token_list = NULL;
	return ;
}
//もともとget_next_tokenで条件分岐していた処理を、関数ポインタで短くする。
const t_state_func_row *init_state_func_table(void)
{
	t_state_func_row	*array;
		// {NULL,"NEUTRAL", NULL},
	const t_state_func_row state_func_table = {
		{'>',"GTGT", &lex_gtgt},
		{'<',"LTLT", &lex_ltlt},
		{'\'',"IN_SINGLE_QUOTE", &lex_single_quote},
		{'\"',"IN_DOUBLE_QUOTE", &lex_double_quote},
		{'$',"VARIABLE", &lex_variable},
		{'0', "NOWHRE", NULL},
	};
	// array = (t_state_func_row *)malloc(sizeof(t_state_func_row) * 7);
	// array = state_func_table;
	return (state_func_table);
};
void	*tokenizer(char *line)
{
	t_state_func_row	*state_func_table;
	int					i;
	t_lex_arg 			*l;
	t_state_func_row	*state_func_table;

	i = 0;
	state_func_table = init_state_func_table();
	init_lex_arg(l, line);//lineを削除します。
	while (line[i] != '\0')
	{
		find_match_state(line, state_func_table);
	}
	return ;
}

int	main()
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