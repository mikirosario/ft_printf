/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:08:15 by mrosario          #+#    #+#             */
/*   Updated: 2019/11/11 22:34:19 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, void const *src, int c, size_t n)
{
	unsigned char		usc;
	unsigned char		*pdst;
	unsigned char const	*psrc;

	usc = (unsigned char)c;
	if (n > 0)
	{
		pdst = dst;
		psrc = src;
		while (n-- > 0)
		{
			if (*psrc == usc)
			{
				*pdst = *psrc;
				return (++pdst);
			}
			else
				*pdst++ = *psrc++;
		}
	}
	return (0);
}
