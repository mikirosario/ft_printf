/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:57:18 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/18 18:23:18 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_intchar(char *c, size_t endpos, long long int n, int base)
{
	while (endpos > 0 && n > 0)
	{
		c[--endpos] = n % base < 10 ? (n % base) + 48 : (n % base) + 55;
		n = n / base;
	}
	return (c);
}

char		*ft_llitoa_base(long long int num, int base)
{
	size_t				bytes;
	long long int		ncpy;
	char				*ptr;

	if (base < 2 || base > 36)
		return (ptr = ft_strdup("ft_llitoa_base supports base values 2-32"));
	if (num == 0)
	{
		if (!(ptr = ft_calloc(2, sizeof(char))))
			return (ptr);
		*ptr = '0';
		return (ptr);
	}
	bytes = 1;
	ncpy = num < 0 ? num * -1 : num;
	while ((ncpy = ncpy / base) > 0)
		bytes++;
	ncpy = num < 0 ? num * -1 : num;
	bytes = num < 0 ? bytes + 2 : bytes + 1;
	if (!(ptr = ft_calloc((bytes), sizeof(char))))
		return (ptr);
	*ptr = num < 0 ? '-' : *ptr;
	return (ft_intchar(ptr, bytes - 1, ncpy, base));
}
