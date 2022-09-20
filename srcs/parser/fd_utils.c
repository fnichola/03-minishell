/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:42:50 by akihito           #+#    #+#             */
/*   Updated: 2022/09/04 21:24:44 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	operation_file_fds(t_parse_arg *p)
{
	int		redct_fd_in;
	int		redct_fd_out;
	char	*file_name;
	int		old_fd[2];

	printf("operation_file_fds\n");
	old_fd[0] = dup(STDIN_FILENO);//ここが親プロセスでfdを変換している
	old_fd[1] = dup(STDOUT_FILENO);
	file_name = ft_strdup(p->token->word);
	// printf("file_name %s\n", file_name);
	redct_fd_out = open(file_name, O_CREAT|O_WRONLY|O_TRUNC, 0666);
	printf("redct_fd_in %d\n", redct_fd_out);
	// dup2(redct_fd_in, STDIN_FILENO);
	dup2(redct_fd_out, STDOUT_FILENO);//ここでリダイレクト
	close(redct_fd_out);
	printf("after\n");
	// dup2(old_fd[1], STDOUT_FILENO);
	// printf("dup2(old_fd[1], STDOUT_FILENO);");
	// close(old_fd[1]);
	
	// redct_fd_in = open(file_name, O_RDWR);
	// printf("g_data.exec_fds[g_data.cmd_index] %d\n", g_data.exec_fds[g_data.cmd_index]);
	// dup2((g_data.exec_fds[g_data.cmd_index])[0], STDIN_FILENO);
	// dup2(open(p->token->word,  O_WRONLY|O_CREAT|O_TRUNC, 0666), STDIN_FILENO);
	// dup2((g_data.exec_fds[g_data.cmd_index])[1], STDOUT_FILENO);

	// printf("p->token->word %s\n",p->token->word);
	// printf("redct_fd_in %d\n", redct_fd_in);
	// printf("p->command->output_file %d\n", p->command->output_file);
	return ;
}
// dup2(open(open(p->token->word,  O_WRONLY|O_CREAT|O_TRUNC, 0666)));
// int	ft_open(t_iolist *filenode, int flags, mode_t mode)
// {
// 	int	fd;

// 	if (mode == 0)
// 		fd = open(filenode->str, flags);
// 	else
// 		fd = open(filenode->str, flags, mode);
// 	if (fd == -1)
// 	{
// 		ft_putstr_fd("minishell: ", STDERR_FILENO);
// 		ft_putstr_fd(filenode->str, STDERR_FILENO);
// 		ft_putstr_fd(": ", STDERR_FILENO);
// 		perror("");
// 	}
// 	return (fd);
// }
