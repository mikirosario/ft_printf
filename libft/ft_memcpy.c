/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:31:28 by mrosario          #+#    #+#             */
/*   Updated: 2019/11/11 22:25:32 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void const *src, size_t n)
{
	char		*d;
	char const	*s;

	d = dst;
	s = src;
	if (dst || src)
	{
		while (n-- > 0)
			*d++ = *s++;
	}
	return (dst);
}
