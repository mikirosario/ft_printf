/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 21:53:38 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/22 08:25:17 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_intchar(char *c, size_t endpos, unsigned long long int n)
{
	while (endpos > 0 && n > 0)
	{
		c[--endpos] = (n % 10) + 48;
		n = n / 10;
	}
	return (c);
}

char		*ft_llitoa(long long int n)
{
	size_t						byte;
	unsigned long long int		ncpy;
	char						*ptr;

	if (n == 0)
	{
		if (!(ptr = ft_calloc(2, sizeof(char))))
			return (ptr);
		*ptr = '0';
		return (ptr);
	}
	byte = 1;
	ncpy = n < 0 ? n * -1 : n;
	while ((ncpy = ncpy / 10) > 0)
		byte++;
	ncpy = n < 0 ? n * -1 : n;
	byte = n < 0 ? byte + 2 : byte + 1;
	if (n > 0)
		if (!(ptr = ft_calloc((byte), sizeof(char))))
			return (ptr);
	if (n < 0)
		if (!(ptr = ft_calloc((byte), sizeof(char))))
			return (ptr);
	*ptr = n < 0 ? '-' : 0;
	return (ft_intchar(ptr, byte - 1, ncpy));
}
