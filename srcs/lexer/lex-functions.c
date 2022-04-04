/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex-functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:58:17 by fnichola          #+#    #+#             */
/*   Updated: 2022/04/04 21:06:49 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	lex_neutral(t_lex_arg *l)
{
	printf("[NEUTRAL]\n");
	if (!(l->line)[l->i])
		l->state = END_OF_LINE;
	else if (is_space((l->line)[l->i]))
	{
		l->start_index = l->i + 1;
		l->state = NEUTRAL;
	}
	else
		l->state = IN_WORD;
}

// void	lex_gtgt(t_lex_arg *l)
// {
// 	if (l->line[*(l->i)] == '>')
// 		l->token_type = T_GTGT;		slice_new_token(l, 2, T_GTGT);
// 	}
// 		l->token_type = T_GT;//w_token(l, 2, T_GTGT);
// 	(l->i)++;
// 	return ;
// }

// void	lex_ltlt(t_lex_arg *l)
// {
// 	if (l->line[*(l->i)] == '<')
// 	{
// 			slice_new_token(l, 1, T_LT);
// 	return ;
// }

// void	lex_in_single_quote(t_lex_arg *l)
// {
// 	if (l->line[*(l->i)] == '\'')
// 	{
// 		slice_new_token(l, *(l->i) - (l->start_index) - 1, T_WORD);
// 	}
// 	(l->i)++;
// }

// void	lex_in_double_quote(t_lex_arg *l)
// {
// 	if (l->line[*(l->i)] == '\"')
// 	{
// 		slice_new_token(l, *(l->i) - (l->start_index) - 1, T_WORD);
// 	}
// 	(l->i)++;
// }

// void	lex_variable(t_lex_arg *l)
// {
// )
// 		slice_new_token(l, *(l->i) - (l->start_index), T_VAR);
// 	else
// 		(l->i)++;
// 	return ;
// }

void	lex_in_word(t_lex_arg *l)
{
	printf("[IN_WORD]\n");
	if (is_delimeter((l->line)[l->i]) || !(l->line)[l->i])
	{
		l->token_type = T_WORD;
		l->state = RETURN_TOKEN;
	}
}

void	lex_end_of_line(t_lex_arg *l)
{
	printf("[END_OF_LINE]\n");
	l->token_type = T_EOL;
	l->state = RETURN_TOKEN;

}
