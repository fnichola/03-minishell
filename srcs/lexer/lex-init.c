#include "minishell.h"
#include "lexer.h"

const t_state_func_row *init_state_func_table(void)
{
	const t_state_func_row temp[] = {
		{NEUTRAL,				&lex_neutral},
		{GTGT,					&lex_gtgt},
		{LTLT,					&lex_ltlt},
		{BEGIN_SINGLE_QUOTE,	&lex_begin_single_quote},
		{IN_SINGLE_QUOTE,		&lex_in_single_quote},
		{BEGIN_DOUBLE_QUOTE,	&lex_begin_double_quote},
		{IN_DOUBLE_QUOTE,		&lex_in_double_quote},
		{VARIABLE,				&lex_variable},
		{IN_WORD,				*lex_in_word},
		{END_OF_LINE,			*lex_end_of_line}
	};
	t_state_func_row	*state_func_table;
	state_func_table = malloc_error_check(sizeof(temp));
	ft_memcpy(state_func_table, temp, sizeof(temp));//constだとスコープがその関数内だけだが、memcpyでコピーしたアドレスはreturnできる。

	return (state_func_table);
};

void	init_lex_arg(t_lex_arg *l, char *line)
{
	l->line = line;
	l->i = 0;
	l->start_index = 0;
	l->state = NEUTRAL;
	l->found_token = false;
	return ;
}
