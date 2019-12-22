/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 03:22:29 by mrosario          #+#    #+#             */
/*   Updated: 2019/11/21 16:37:37 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** Index[0] = rowindex, Index[1] = rowlen, Index[2] = colindex
*/

static size_t	ft_colcounter(char const *s, char c)
{
	size_t	rowlen;

	rowlen = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s && *s++ != c)
			while (*s == c && c)
			{
				if (*(s - 1) != c)
					rowlen++;
				s++;
			}
		if (*(s - 1) != c)
			rowlen++;
	}
	return (++rowlen);
}

static size_t	ft_collen(char const *s, char c)
{
	size_t	collen;

	collen = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s && *s++ != c)
			collen++;
	}
	return (collen);
}

char			**ft_split(char const *s, char c)
{
	char	*i;
	char	**ptr;
	size_t	index[3];

	index[0] = 0;
	index[2] = 0;
	if (!s)
		return (NULL);
	i = ft_strtrim(s, (char[2]) {c, '\0'});
	index[1] = ft_colcounter(i, c);
	if (!(ptr = ft_calloc(index[1], sizeof(char *))))
		return (NULL);
	while (index[1]-- > 1)
	{
		if (!(ptr[index[0]] = ft_calloc(ft_collen(i, c) + 1, sizeof(char))))
			return (NULL);
		while (*i != c && *i)
			ptr[index[0]][index[2]++] = *i++;
		index[2] = 0;
		index[0]++;
		while (*i == c && *i)
			i++;
	}
	ptr[index[0]] = NULL;
	return (ptr);
}
