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
	return (token);
}


t_token	*lex_neutral()
{

}

void	lex_variable(t_lex_arg *l)
{
	if (!l->line[*(l->i)] || is_delimeter(l->line[*(l->i)]))
		return (slice_new_token(l->line, l->start_index, l->i - l->start_index, T_VAR));
	*(l->i)++;
}

void	lex_gtgt(t_lex_arg *l)
{
	if (l->line[*(l->i)] == '>')
	{
		*(l->i)++;
		return (slice_new_token(l, 2, T_GTGT));
	}
	else
		return (slice_new_token(l, 2, T_GTGT));
	*(l->i)++;
}

t_state_func_row **init_state_func_table(void)
{
	const t_state_func_row *state_func_table[] = {
		{"NEUTRAL", &lex_neutral},
		{"GTGT", &lex_gtgt},
		{"LTLT", &lex_ltlt},
		{"IN_SINGLE_QUOTE", &lex_single_quote},
		{"IN_DOUBLE_QUOTE", &lex_double_quote},
		{"VARIABLE", &lex_variable}
	};
	return (state_func_table);
};

//もともとget_next_tokenで条件分岐していた処理を、関数ポインタで短くする。
t_list	*tokenizer(char *line)
{
	t_state_func_row	**state_func_table;
	int					i;

	i = 0;
	state_func_table = init_state_func_table();

	while (line[i] != NULL)
	{
		i++;
	}
	return ();
}