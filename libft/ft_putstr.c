/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 11:53:36 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/16 01:10:30 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

size_t	ft_putstr(char const *str, size_t len)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (len && len-- && str[i])
			write(1, &str[i++], 1);
	}
	return (i);
}
