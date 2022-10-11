
#include <stdarg.h>
#include "minishell.h"

void	debug_log(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	printf("\033[1;33m"); // set to yellow
	vprintf(format, args);
	printf("\033[0m"); // reset to black
	fflush(stdout);
	va_end(args);
}
