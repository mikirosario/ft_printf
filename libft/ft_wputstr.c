/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wputstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 09:24:06 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/22 09:29:43 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

size_t	ft_wputstr(wchar_t const *str, size_t len)
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
