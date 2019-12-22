/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lluitoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 07:37:47 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/22 15:21:30 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_intchar(char *c, size_t endpos, \
		unsigned long long int n, int base)
{
	while (endpos > 0 && n > 0)
	{
		c[--endpos] = n % base < 10 ? (n % base) + 48 : (n % base) + 55;
		n = n / base;
	}
	return (c);
}

char		*ft_lluitoa_base(unsigned long long int num, int base)
{
	size_t						bytes;
	unsigned long long int		ncpy;
	char						*ptr;

	if (base < 2 || base > 36)
		return (ptr = ft_strdup("ft_lluitoa_base supports base values 2-32"));
	if (num == 0)
	{
		if (!(ptr = ft_calloc(2, sizeof(char))))
			return (ptr);
		*ptr = '0';
		return (ptr);
	}
	bytes = 1;
	ncpy = num;
	while ((ncpy = ncpy / base) > 0)
		bytes++;
	ncpy = num;
	bytes++;
	if (!(ptr = ft_calloc((bytes), sizeof(char))))
		return (ptr);
	return (ft_intchar(ptr, bytes - 1, ncpy, base));
}
