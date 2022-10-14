/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:32:22 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 08:34:49 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirects(t_redirect **redirect_list)
{
	t_redirect	*ptr;
	t_redirect	*tmp;

	ptr = *redirect_list;
	while (ptr)
	{
		free(ptr->filename);
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	*redirect_list = NULL;
}
