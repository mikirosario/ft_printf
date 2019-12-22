/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 22:07:54 by mrosario          #+#    #+#             */
/*   Updated: 2019/11/13 19:22:46 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char const *str)
{
	char const			*ptr;
	int					base;
	long unsigned int	res;
	int					sign;

	ptr = str;
	base = 10;
	sign = 1;
	res = 0;
	while (*ptr == '\t' || *ptr == '\n' || *ptr == '\v' ||
			*ptr == '\f' || *ptr == '\r' || *ptr == ' ')
		ptr++;
	if (*ptr == '-')
	{
		ptr++;
		sign = -1;
	}
	else if (*ptr == '+')
		ptr++;
	while (ft_isdigit(*ptr))
		res = (res * base) + (*ptr++ - 48);
	if (res < 2147483649)
		return ((int)res * sign);
	return (sign == 1 ? -1 : 0);
}
