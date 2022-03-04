/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/03/04 18:42:27 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

void	exit_error(void)
{
	printf("Error!\n");
	exit(EXIT_FAILURE);
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

t_list	*parse_line(const char *line)
{
	t_list	*command_table;
	char	**split_command;

	command_table = NULL;
	split_command = ft_split(line, ' '); // ignoring pipes, etc, for now
	ft_lstadd_back(&command_table, ft_lstnew(split_command));
	return (command_table);
}

int	execute_commands(t_list *command_table, char **envp)
{
	pid_t	pid;
	int		status;
	char	**argv;

	while (command_table)
	{
		argv = (char **)command_table->content;
		if (!argv || !argv[0])
			return (0);
		if (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])))
		{
			ft_printf("exit\n");
			return (1);
		}
		pid = fork();
		if (pid == 0)
		{
			if (execve(argv[0], argv, envp))
				exit_error();
		}
		else
		{
			waitpid(pid, &status, WUNTRACED);
		}
		command_table = command_table->next;
	}
	return (0);
}

int minishell(char **envp)
{
	t_list	*command_table;
	int		status;
	char	*line;
	//initialize
	command_table = NULL;
	status = 0;
	while (!status)
	{
		line = readline("minishell$ ");
		if (line && *line)
			add_history(line);
		command_table = parse_line(line);
		free(line);
		status = execute_commands(command_table, envp);
		ft_lstclear(&command_table, free_command_array);
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
	// rl_clear_history(); // requires GNU Readline
	return (0);
}
