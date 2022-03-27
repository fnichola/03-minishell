#include "includes/minishell.h"
#include <stdio.h>

struct s_test {
	char symbol;
	char *str;
	void (*test_func)(void);
};

void test_func(void)
{
	printf("test_func\n");
	return ;
}

int	main(void)
{
	// t_state_func_row	*array;
		// {NULL,"NEUTRAL", NULL},
	const struct s_test state_func_table[] = {
		{'>',"GTGT", &test_func},
		{'<',"LTLT", &test_func},
		{'\'',"IN_SINGLE_QUOTE", &test_func},
		{'\"',"IN_DOUBLE_QUOTE", &test_func},
		{'$',"VARIABLE", &test_func},
		{'0', "NOWHRE", NULL},
	};
	printf("%s\n",state_func_table[0].str);
	state_func_table[0].test_func();
	// array = (t_state_func_row *)malloc(sizeof(t_state_func_row) * 7);
	// array = state_func_table;
	return (0);
};