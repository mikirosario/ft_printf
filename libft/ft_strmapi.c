/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:11:04 by mrosario          #+#    #+#             */
/*   Updated: 2019/11/13 12:38:53 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			strlen;
	char			*res;

	if (!s || !f)
		return (0);
	strlen = ft_strlen(s);
	if (!(res = ft_calloc(strlen + 1, sizeof(char))))
		return (res);
	ft_memcpy(res, s, strlen);
	i = 0;
	while (res[i])
	{
		res[i] = (*f)(i, res[i]);
		i++;
	}
	return (res);
}
