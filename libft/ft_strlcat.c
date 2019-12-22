/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:14:22 by mrosario          #+#    #+#             */
/*   Updated: 2019/11/09 11:56:35 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, char const *src, size_t dstsize)
{
	char		*pdst;
	char const	*psrc;
	size_t		n;
	size_t		dstlen;

	pdst = dst;
	psrc = src;
	n = dstsize;
	while (n-- > 0 && *pdst != '\0')
		pdst++;
	dstlen = pdst - dst;
	n = dstsize - dstlen;
	if (n == 0)
		return (dstlen + ft_strlen(psrc));
	while (*psrc != '\0')
	{
		if (n != 1)
		{
			*pdst++ = *psrc;
			n--;
		}
		psrc++;
	}
	*pdst = '\0';
	return (dstlen + (psrc - src));
}
