/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 05:19:06 by fnichola          #+#    #+#             */
/*   Updated: 2022/08/17 11:58:03 by fnichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_splits(char *s, char c, size_t wordcount)
{
	size_t	i;

	if (!*s)
		return (wordcount);
	while (*s == c && *s)
		s++;
	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (i > 0)
		return (count_splits(s + i, c, wordcount + 1));
	return (wordcount);
}

static void	free_array(char **arr, size_t wordcount)
{
	size_t	i;

	i = 0;
	while (i < wordcount)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

static char	**make_splits(char **ret, char *s, char c, size_t wordcount)
{
	size_t	count;
	size_t	i;
	char	*substring;

	count = 0;
	while (count < wordcount)
	{
		while (*s == c && *s)
			s++;
		i = 0;
		while (s[i] != c && s[i])
			i++;
		substring = (char *)ft_calloc(i + 1, sizeof(char));
		if (!substring)
		{
			free_array(ret, wordcount);
			return (NULL);
		}
		ft_strlcpy(substring, s, i + 1);
		s += i;
		ret[count++] = substring;
	}
	return (ret);
}

/**
 * Allocates (with malloc(3)) and returns an array of strings obtained by
 * splitting ’s’ using the character ’c’ as a delimiter.
 * The array must be ended by a NULL pointer.
*/
char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	wordcount;

	if (!s)
		return (NULL);
	wordcount = count_splits((char *)s, c, 0);
	ret = (char **)ft_calloc(wordcount + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	return (make_splits(ret, (char *)s, c, wordcount));
}
