/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/05/20 12:55:56 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

size_t	argv_len(char **argv)
{
	size_t	i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}

void	free_command_table(void *ptr)
{
	size_t	i;
	t_command	*command;

	command = (t_command *)ptr;
	i = 0;
	while (command->argv && command->argv[i])
	{
		free(command->argv[i]);
		i++;
	}
	free(command->argv);
	free(command);
}

void	builtin_exit(int argc, char **argv)
{
	int	ret;

	if (argc == 1)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else if (argc == 2)
	{
		printf("exit\n");
		ret = ft_atoi(argv[1]);
		exit(ret);
	}
	else
	{
		printf("too many arguments\n"); // need a separate error function
	}
}

void free_token_list (void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	free(token->word);
	free(token);

}

void	search_path_and_exec(char **argv, char **envp)
{
	char	**paths;
	char	*pathname;
	char	*temp;
	size_t	i;

	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		pathname = ft_strjoin(temp, argv[0]);
		free(temp);
		execve(pathname, argv, envp);
		free(pathname);
		i++;
	}
	free(paths);
	exit_error("Can't find command.");
}


// void	parse_line(const char *line, t_list **command_table)
// {
// 	t_command	*command;
// 	t_list	*tokens;
// 	t_list	*tmp;
// 	size_t	i;

// 	tokens = tokenizer(line);
// 	tmp = tokens;
// 	command = malloc_error_check(sizeof(t_command));
// 	command->argv = malloc_error_check(sizeof(char *) * 32);
// 	command->output_file = NULL;
// 	command->input_file = NULL;
// 	command->error_file = NULL;
	
// 	i = 0;
// 	while (tmp)
// 	{
// 		command->argv[i] = ((t_token *)tmp->content)->word;
// 		// add real parsing, right now all tokens are just passed to execve
// 		// realloc if more than 32 words
// 		// free token if not used in simple_command
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	command->argv[i] = NULL;
// 	ft_lstadd_back(command_table, ft_lstnew(command));
// 	ft_lstclear(&tokens, free);
// }

int	execute_commands(t_list *command_table, char **envp)
{
	pid_t	pid;
	int		status;
	char	**argv;
	t_command	*command;
	t_list	*ptr;
	int		pfd[2];

	pipe(pfd); // add error check. also don't need this if only one command.
	
	ptr = command_table;
	while (ptr)
	{
		command = (t_command *)ptr->content;
		argv = command->argv;
		if (!argv || !argv[0])
			return (0);
		if (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) && ft_strlen(argv[0]) >= 4)
		{
			builtin_exit(argv_len(argv), argv);
		}
		pid = fork();
		if (pid == 0) // first child
		{
			close(pfd[0]); // close read end of pipe
			if (ptr->next)
			{
				dup2(pfd[1], STDOUT_FILENO);
				close(pfd[1]);
			}

        }

			if (ft_strchr(argv[0], '/'))
				execve(argv[0], argv, envp);
			else
				search_path_and_exec(argv, envp);
		}
		else
		{
			waitpid(pid, &status, WUNTRACED);
		}
		ptr = ptr->next;
	}
	return (0);
}

int minishell(char **envp)
{
	t_list	*command_table;
	int		status;
	char	*line;

	command_table = NULL;
	status = 0;
	while (!status)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		// parse_line(line, &command_table);
		t_list *tokens = tokenizer(line);
		command_table = parser(tokens);
		free(line);
		status = execute_commands(command_table, envp);
		ft_lstclear(&command_table, free_command_table);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc == 1)
	{
		minishell(envp);
	}
	else
	{
		ft_printf("error\n");
	}
	return (0);
}
