/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute-commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 09:22:05 by fnichola          #+#    #+#             */
/*   Updated: 2022/09/28 17:31:33 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool	lookup_and_exec_built_in(char **argv)
{
	bool	is_builtin;
	size_t	i;
	char	*str;

	str = str_tolower(argv[0]);
	is_builtin = false;
	i = 0;
	while (i < g_data.num_built_ins)
	{
		if (is_str_match(str, g_data.built_ins[i].name))
		{
			g_data.built_ins[i].func(argv);
			is_builtin = true;
			break ;
		}
		i++;
	}
	free(str);
	return (is_builtin);
}

bool	execute_built_in(char **argv)
{
	bool	is_builtin;
	int		old_fd[2];

	old_fd[0] = dup(STDIN_FILENO);
	old_fd[1] = dup(STDOUT_FILENO);
	dup2((g_data.exec_fds[g_data.cmd_index])[0], STDIN_FILENO);
	dup2((g_data.exec_fds[g_data.cmd_index])[1], STDOUT_FILENO);
	is_builtin = lookup_and_exec_built_in(argv);
	dup2(old_fd[0], STDIN_FILENO);
	close(old_fd[0]);
	dup2(old_fd[1], STDOUT_FILENO);
	close(old_fd[1]);
	return (is_builtin);
}

void	search_path_and_exec(char **argv, char **envp)
{
	char	**paths;
	char	*pathname;
	char	*temp;
	size_t	i;

	printf("search\n");
	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		pathname = ft_strjoin(temp, argv[0]);
		free(temp);
		execve(pathname, argv, envp);
		free(pathname);
		free(paths[i]);
		paths[i] = NULL;
		i++;
	}
	free(paths);
	exit_error("Can't find command.");
}

int		execute_external(char **argv, char **envp)
{
	pid_t	pid;
	// int		status;

	pid = fork();
	if (pid == 0)// 子プロセス
	{
		dup2((g_data.exec_fds[g_data.cmd_index])[0], STDIN_FILENO);
		dup2((g_data.exec_fds[g_data.cmd_index])[1], STDOUT_FILENO);
		close_exec_fds();
		if (ft_strchr(argv[0], '/'))
			execve(argv[0], argv, envp);
		else
			search_path_and_exec(argv, envp);
	}
	else // 親プロセス
	{
		// printf("external\n");
		if (g_data.cmd_index == g_data.num_cmds - 1)
		{
			close_exec_fds();
			// waitpid(pid, &status, WUNTRACED);
		}
		// printf("external2\n");
		// printf("pid %d\n", pid);
	}
	// printf("pid %d\n", pid);
	return (pid);
}

static void	execute_simple_command(char **argv, pid_t *pids, int i)
{
	char	**envp;
	// pid_t	tmp;

	(void)pids;
	(void)i;
	// tmp = 0;
	if (execute_built_in(argv))
		return ;
	else
	{
		printf("test\n");
		envp = export_to_envp();
		printf("test2\n");
		// tmp = execute_external(argv, envp);
		pids[i] = execute_external(argv, envp);
		// printf("tmp = %d\n", tmp);
		// printf("pids[i] %d \n", pids[i]);
		free_envp(envp);
	}
}

static void	execute_commands_loop(t_list *command_table_ptr)
{
	t_command	*command;
	char		**argv;
	size_t		i;
	pid_t		*pids;
	int			status;
	// pids = (pid_t *)malloc_error_check(g_data.num_cmds);
	printf("g_data.num_cmds %zu\n", g_data.num_cmds);
	pids = (pid_t *)malloc(sizeof(pid_t) * (g_data.num_cmds + 1));
	g_data.cmd_index = 0;
	while (g_data.cmd_index < g_data.num_cmds)//num_cmdsはパイプがあれば、増えていく
	{
		command = (t_command *)command_table_ptr->content;
		argv = command->argv;//ここでargvにcommandのargvが代入されているので、built_inにはargvを渡せばいい。
		if (!argv || !argv[0])
			return ;
		execute_simple_command(argv, pids, g_data.cmd_index);
		command_table_ptr = command_table_ptr->next;
		g_data.cmd_index++;
	}
	i = 0;
	while (i < g_data.num_cmds + 1)
	{
		printf("while %d \n", pids[i]);
		waitpid(pids[i], &status, WUNTRACED);
		i++;
	}
	free(pids);
}

int	execute_commands(void)
{
	g_data.num_cmds = ft_lstsize(g_data.command_table);
	init_exec_fds();
	execute_commands_loop(g_data.command_table);
	free_exec_fds();
	return (0);
}
