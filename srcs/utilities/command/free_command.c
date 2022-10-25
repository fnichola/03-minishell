/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 02:53:05 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/25 13:21:52 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_command *cmd)
{
	size_t		i;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);
	i = 0;
	while (cmd->heredoc && cmd->heredoc[i])
	{
		free(cmd->heredoc[i]);
		i++;
	}
	free(cmd->heredoc);
	free_redirects(&cmd->redirects);
	free(cmd);
}
