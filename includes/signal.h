/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:20:51 by akihito           #+#    #+#             */
/*   Updated: 2022/10/19 18:18:18 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../libft/libft.h"
# include "minishell.h"
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>

void	sig_handler(int signum);
void	signal_handler(int signo);
#endif
