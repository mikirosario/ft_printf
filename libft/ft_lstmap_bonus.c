/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 17:52:00 by mrosario          #+#    #+#             */
/*   Updated: 2019/11/21 16:48:42 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *))
{
	t_list *cpy;
	t_list *orig;
	t_list *start;

	start = NULL;
	if (l)
	{
		start = ft_lstnew(l->content);
		orig = start;
		while (l->next)
		{
			l = l->next;
			cpy = ft_lstnew(l->content);
			orig->next = cpy;
			orig = cpy;
		}
		cpy = start;
		while (cpy)
		{
			if (!(cpy->content = f(cpy->content)))
				del(cpy->content);
			cpy = cpy->next;
		}
	}
	return (start);
}
