/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:04:09 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/13 08:44:41 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*redirect_new(void)
{
	t_redirect	*new_redirect;

	new_redirect = malloc_error_check(sizeof(t_redirect));
	new_redirect->type = UNDEFINED_REDIRECT;
	new_redirect->filename = NULL;
	new_redirect->append = false;
	new_redirect->next = NULL;
	return (new_redirect);
}
