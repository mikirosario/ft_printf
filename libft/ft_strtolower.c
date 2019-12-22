/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:43:18 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/18 19:18:52 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtolower(char *str)
{
	char *ptr;

	ptr = str;
	if (str && *str)
	{
		while (*ptr)
		{
			*ptr = ft_tolower(*ptr);
			ptr++;
		}
	}
	else
		str = NULL;
	return (str);
}
