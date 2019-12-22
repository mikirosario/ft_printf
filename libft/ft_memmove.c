/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:52:30 by mrosario          #+#    #+#             */
/*   Updated: 2019/11/11 22:38:04 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void const *src, size_t len)
{
	char		*pdst;
	char const	*psrc;
	char		*plastd;
	char const	*plasts;

	if (!(dst) && !(src))
		return (dst);
	pdst = dst;
	psrc = src;
	if (pdst < psrc)
		while (len-- > 0)
			*pdst++ = *psrc++;
	else
	{
		plastd = pdst + (len - 1);
		plasts = psrc + (len - 1);
		while (len-- > 0)
			*plastd-- = *plasts--;
	}
	return (dst);
}
