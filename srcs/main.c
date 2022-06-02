/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:46:58 by fnichola          #+#    #+#             */
/*   Updated: 2022/05/23 15:49:29 by fnichola         ###   ########.fr       */
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

pid_t	execute_simple_command(char **argv, char **envp, t_exec_fds exec_fds)
{
	pid_t	pid;

	if (!ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) && ft_strlen(argv[0]) >= 4)
	{
		builtin_exit(argv_len(argv), argv);
	}
	pid = fork();
	if (pid == 0)
	{
		close(exec_fds.in_fd);
		close(exec_fds.out_fd);
		close(exec_fds.pipe_fd[0]);
		close(exec_fds.pipe_fd[1]);
		if (ft_strchr(argv[0], '/'))
			execve(argv[0], argv, envp);
		else
			search_path_and_exec(argv, envp);
	}
	return(pid);
}

void	execute_last_command(char **argv, char **envp, t_exec_fds *exec_fds)
{
	pid_t	pid;
	int		status;

	dup2(exec_fds->out_fd, STDOUT_FILENO);
	close(exec_fds->out_fd);
	exec_fds->out_fd = -1;
	pid = execute_simple_command(argv, envp, *exec_fds);
	dup2(exec_fds->in_fd, STDIN_FILENO);
	close(exec_fds->in_fd);
	waitpid(pid, &status, WUNTRACED);
}

void	execute_piped_command(char **argv, char **envp, t_exec_fds *exec_fds)
{
	pipe(exec_fds->pipe_fd);
	dup2(exec_fds->pipe_fd[1], STDOUT_FILENO);
	close(exec_fds->pipe_fd[1]);
	execute_simple_command(argv, envp, *exec_fds);
	dup2(exec_fds->pipe_fd[0], STDIN_FILENO);
	close(exec_fds->pipe_fd[0]);
}

int	execute_commands(t_list *command_table, char **envp)
{
	t_command	*command;
	char		**argv;
	int			number_of_simple_commands;
	int			i;
	t_exec_fds	exec_fds;

	i = 0;
	number_of_simple_commands = ft_lstsize(command_table);
	exec_fds.in_fd = dup(STDIN_FILENO);
	exec_fds.out_fd = dup(STDOUT_FILENO);
	while (i < number_of_simple_commands)
	{
		command = (t_command *)command_table->content;
		argv = command->argv;
		if (!argv || !argv[0])
			return (0);
		if (i == number_of_simple_commands - 1) // last simple command
			execute_last_command(argv, envp, &exec_fds);
		else // not the last simple command
			execute_piped_command(argv, envp, &exec_fds);
		command_table = command_table->next;
		i++;
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


