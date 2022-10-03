/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:15:34 by akihito           #+#    #+#             */
/*   Updated: 2022/09/30 22:19:30 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool	launch_expand_redirect(t_parse_arg *p)
// {
// 	t_redirect	*redirect;
// 	int			flg;

// 	redirect = cmd_list->redirect;
// 	flg = 0;
// 	while (redirect != NULL && redirect->file_name != NULL)
// 	{
// 		if (redirect->redirect_type == 1)
// 			cmd_list->fd_out = redirect_open_out \
// 									(redirect->file_name, false, &flg);
// 		else if (redirect->redirect_type == 2)
// 			cmd_list->fd_out = redirect_open_out \
// 									(redirect->file_name, true, &flg);
// 		else if (redirect->redirect_type == 3)
// 			cmd_list->fd_in = redirect_open_in(redirect->file_name, &flg);
// 		else if (redirect->redirect_type == 4)
// 			cmd_list->fd_in = launch_heredoc(redirect->file_name, &flg);
// 		if (flg)
// 			return (false);
// 		redirect = redirect->next;
// 	}
// 	return (true);
// }

int	redirect_open_out(char *filename, bool is_append, int *flg)
{
	int	fd;

	printf("filename = %s\n", filename);
	if (is_append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);//0666は作成時の権限
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_perror(filename);
		*flg = 1;
	}
	return (fd);
}
