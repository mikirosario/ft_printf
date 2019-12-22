/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:35:18 by mrosario          #+#    #+#             */
/*   Updated: 2019/11/10 17:27:42 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s1)
{
	size_t	strsize;
	char	*ptr;

	strsize = (ft_strlen(s1)) + 1;
	if (!(ptr = ft_calloc(strsize, 1)))
		return (ptr);
	ft_memcpy(ptr, s1, strsize);
	return (ptr);
}
