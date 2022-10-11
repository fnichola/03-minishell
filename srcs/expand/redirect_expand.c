/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:15:34 by akihito           #+#    #+#             */
/*   Updated: 2022/10/11 06:55:01 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	redirect_open_out(char *filename, bool is_append, int *flg)
{
	int	fd;

	debug_log("filename = %s\n", filename);
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
