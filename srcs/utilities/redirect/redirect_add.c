/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:12:38 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/30 15:05:18 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*redirect_add(t_redirect **redirect_list, t_redirect *new_redirect)
{
	t_redirect	*ptr;

	if (!*redirect_list)
		*redirect_list = new_redirect;
	else
	{
		ptr = *redirect_list;
		while (ptr && ptr->next)
			ptr = ptr->next;
		ptr->next = new_redirect;
	}
	return (new_redirect);
}
