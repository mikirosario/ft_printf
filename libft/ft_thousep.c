/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thousep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 19:42:54 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/21 02:24:22 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_sepcount(char *numstr, int strlen)
{
	int		comcount;
	int		newlen;

	comcount = 0;
	if (numstr[0] != '-' && strlen > 3)
		comcount = 1 + ((strlen - 4) / 3);
	else if (numstr[0] == '-' && strlen > 4)
		comcount = 1 + ((strlen - 5) / 3);
	newlen = comcount + strlen;
	return (newlen);
}

char		*ft_thousep(char *numstr, char sep)
{
	int		strlen;
	int		comi;
	int		newlen;
	char	*sepnum;

	comi = 0;
	if (!numstr || (!(ft_isprint(sep))))
		return (NULL);
	strlen = ft_strlen(numstr);
	newlen = ft_sepcount(numstr, strlen--);
	if (!(sepnum = ft_calloc(1 + newlen--, sizeof(char))))
		return (NULL);
	if (numstr[0] == '-')
	{
		sepnum[0] = numstr[0];
		strlen--;
		numstr++;
	}
	while (strlen >= 0 && numstr[strlen] != '-')
	{
		comi == 3 ? (sepnum[newlen--] = sep) : \
					(sepnum[newlen--] = numstr[strlen--]);
		comi == 3 ? comi -= 3 : comi++;
	}
	return (sepnum);
}
