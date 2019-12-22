/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:20:33 by mrosario          #+#    #+#             */
/*   Updated: 2019/11/13 19:25:38 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcpy(char *dst, char const *src, size_t dstsize)
{
	size_t srcsize;

	if (!dst)
		return (0);
	srcsize = ft_strlen(src);
	if (srcsize + 1 < dstsize)
		ft_memcpy(dst, src, srcsize + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (srcsize);
}
