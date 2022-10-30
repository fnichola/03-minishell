/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in-unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 11:46:37 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 11:46:51 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_unset(char **argv)
{
	size_t	i;

	i = 1;
	while (argv[i])
	{
		ft_unsetenv(argv[i]);
		i++;
	}
	g_data.exit_status = 0;
}
