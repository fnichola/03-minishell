#include "minishell.h"
#include "lexer.h"

const t_state_func_row *init_state_func_table(void)
{
	const t_state_func_row temp[] = {
		{NEUTRAL,			&lex_neutral},
		{GTGT,				NULL},
		{LTLT,				NULL},
		{IN_SINGLE_QUOTE, 	NULL},
		{IN_DOUBLE_QUOTE, 	NULL},
		{VARIABLE,			NULL},
		{IN_WORD,			*lex_in_word},
		{END_OF_LINE,		*lex_end_of_line},
		{RETURN_TOKEN,		NULL}
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
	return ;
}
