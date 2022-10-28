/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:05:24 by fnichola          #+#    #+#             */
/*   Updated: 2022/10/21 13:05:46 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_token(void *token_ptr)
{
	t_token	*token;

	token = (t_token *)token_ptr;
	if (token)
	{
		free(token->word);
		token->word = NULL;
		free(token);
		token = NULL;
	}
}
