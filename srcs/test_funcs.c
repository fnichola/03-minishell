#include <stdio.h>
#include "includes/minishell.h"
#include <termios.h>

int main(void)
{
	struct termios	term1, term0;
	int	ch;

	tcgetattr(0, &term1);
	term0 = term1;
	term1.c_lflag &= ~(ICANON | ECHO);
	term1.c_cc[VMIN] = 1;
	term1.c_cc[VTIME] = 0;
	tcsetattr
}