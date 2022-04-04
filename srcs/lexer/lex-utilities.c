#include "minishell.h"
#include "lexer.h"

void	del_token(void *token_ptr)
{
	t_token	*token;

	token = (t_token *)token_ptr;
	free(token->word);
	token->word = NULL;
	free(token);
	token = NULL;
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

bool	is_space(char c)
{
	if((c >= '\t' && c <= '\r')|| c == ' ')
		return (true);
	else
		return (false);
}

char	*token_type_to_str(t_token_type token_type)
{
	if (token_type == T_WORD)
		return ("T_WORD");
	else if (token_type == T_PIPE)
		return ("T_PIPE");
	else if (token_type == T_GT)
		return ("T_GT");
	else if (token_type == T_GTGT)
		return ("T_GTGT");
	else if (token_type == T_LT)
		return ("T_LT");
	else if (token_type == T_LTLT)
		return ("T_LTLT");
	else if (token_type == T_VAR)
		return ("T_VAR");
	else if (token_type == T_EXIT_STATUS)
		return ("T_EXIT_STATUS");
	else if (token_type == T_ERROR)
		return ("T_ERROR");
	else
		return ("bad type!");
}
