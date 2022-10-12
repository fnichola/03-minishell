/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:17:51 by akihito           #+#    #+#             */
/*   Updated: 2022/09/30 18:43:23 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int	redirect_open_out(char *filename, bool is_append, int *flg);

# endif