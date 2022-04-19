/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/04/19 21:56:27 by fnichola         ###   ########.fr       */
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

void	builtin_exit(int argc, char **argv)
{
	if (argc == 1)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else if (argc == 2)
	{
		printf("exit\n");
		exit((unsigned char)ft_atoi(argv[1]));
	}
	else
	{
		printf("too many arguments\n"); // need a separate error function
	}
}

void	free_command_array(void *ptr)
{
	size_t	i;
	char	**array;

	array = (char **)ptr;
	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
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

void	parse_line(const char *line, t_command *command_table)
{
	char	**simple_command;
	t_list	*tokens;
	t_list	*tmp;
	size_t	i;

	tokens = tokenizer(line);
	tmp = tokens;
	simple_command = malloc_error_check(sizeof(char *) * 32);
	i = 0;
	while (tmp)
	{
		simple_command[i] = ((t_token *)tmp->content)->word;
		// add real parsing
		// realloc if more than 32 words
		tmp = tmp->next;
		i++;
	}
	simple_command[i] = NULL;
	ft_lstadd_back(&command_table->simple_commands, ft_lstnew(simple_command));
}

int	execute_commands(t_command *command_table, char **envp)
{
	pid_t	pid;
	int		status;
	char	**argv;
	t_list	*simple_command;
	
	simple_command = command_table->simple_commands;
	while (simple_command)
	{
		argv = (char **)simple_command->content;
		if (!argv || !argv[0])
			return (0);
		if (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) && ft_strlen(argv[0]) >= 4)
		{
			builtin_exit(argv_len(argv), argv);
		}
		pid = fork();
		if (pid == 0)
		{
			if (ft_strchr(argv[0], '/'))
				execve(argv[0], argv, envp);
			else
				search_path_and_exec(argv, envp);
		}
		else
		{
			waitpid(pid, &status, WUNTRACED);
		}
		simple_command = simple_command->next;
	}
	return (0);
}

int minishell(char **envp)
{
	t_command	command_table;
	int		status;
	char	*line;
	//initialize
	command_table.simple_commands = NULL;
	status = 0;
	while (!status)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		parse_line(line, &command_table);
		free(line);
		status = execute_commands(&command_table, envp);
		ft_lstclear(&command_table.simple_commands, free_command_array);
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
