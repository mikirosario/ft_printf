/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:39:53 by mrosario          #+#    #+#             */
/*   Updated: 2019/11/13 22:25:33 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strnstr(char const *hay, char const *needle, size_t len)
{
	size_t needle_len;
	size_t hay_len;

	if (!*needle)
		return ((char *)hay);
	if (len == 0)
		return (0);
	needle_len = ft_strlen(needle);
	hay_len = ft_strlen(hay);
	while (*hay != 0 && len > 0 && hay_len >= needle_len && len-- >= needle_len)
	{
		if (ft_strncmp(needle, hay, needle_len) == 0)
			return (char *)(hay);
		hay++;
		hay_len--;
	}
	return (0);
}
