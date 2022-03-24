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
	ft_lstadd_back(l->token_list, ft_lstnew(token));
	return ;
}

void	lex_netural(t_lex_arg *l)
{
	*(l->i) = 0;
	if (l->line[*(l->i)] == '|')
	{
		*(l->i)++;
		slice_new_token(l, 1, T_PIPE);
	}
	else if (l->line[*(l->i)]) == '$')
	{
		*(l->i)++;
		if ()
	}
}


void	lex_ltlt(t_lex_arg *l)
{
	if (l->line[*(l->i)] == '<')
	{
		*(l->i)++;
		slice_new_token(l, 2, T_LTLT);
	}
	slice_new_token(l, 1, T_LT);
	return ;
}

void	lex_variable(t_lex_arg *l)
{
	if (!l->line[*(l->i)] || is_delimeter(l->line[*(l->i)]))
		slice_new_token(l, *(l->i) - (l->start_index), T_VAR);
	else
		*(l->i)++;
	return ;
}

void	lex_gtgt(t_lex_arg *l)
{
	if (l->line[*(l->i)] == '>')
	{
		*(l->i)++;
		slice_new_token(l, 2, T_GTGT);
	}
	else
		slice_new_token(l, 2, T_GTGT);
	*(l->i)++;
	return ;
}

void	lex_single_quote(t_lex_arg *l)
{
	if (l->line[*(l->i)] == '\'')
	{
		*(l->i)++;
		slice_new_token(l, *(l->i) - (l->start_index) - 1, T_WORD);
	}
	*(l->i)++;
}

void	lex_double_quote(t_lex_arg *l)
{
	if (l->line[*(l->i)] == '\"')
	{
		*(l->i)++;
		slice_new_token(l, *(l->i) - (l->start_index) - 1, T_WORD);
	}
	*(l->i)++;
}

t_state_func_row **init_state_func_table(void)
{
	const t_state_func_row *state_func_table[] = {
		{NULL,"NEUTRAL", &lex_neutral},
		{'>',"GTGT", &lex_gtgt},
		{'<',"LTLT", &lex_ltlt},
		{'\'',"IN_SINGLE_QUOTE", &lex_single_quote},
		{'\"',"IN_DOUBLE_QUOTE", &lex_double_quote},
		{'$',"VARIABLE", &lex_variable}
	};
	return (state_func_table);
};

void	find_match_state(char *line, t_state_func_row *state_func_table)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == state_func_table[i].symbol)
		{
			state_func_table[i].lex

	}
}

void	init_lex_arg(t_lex_arg *l, char *line)
{
	*(l->line) = line;
	*(l->i) = 0;
	l->start_index = 0;
	l->state = neutral;
	l->token_list = NULL;
	return ;
}
//もともとget_next_tokenで条件分岐していた処理を、関数ポインタで短くする。
t_list	*tokenizer(char *line)
{
	t_state_func_row	*state_func_table;
	int					i;
	t_lex_arg 			*l;

	i = 0;
	state_func_table = init_state_func_table();
	init_lex_arg(l, line);
	while (line[i] != '\0')
	{
		find_match_state(line, state_func_table);
	}
	return ();
}