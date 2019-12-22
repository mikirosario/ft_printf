/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:24:57 by mrosario          #+#    #+#             */
/*   Updated: 2019/11/17 16:45:41 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *lst;
	if (lst && *lst)
	{
		while (tmp)
		{
			ft_lstdelone(tmp, del);
			tmp = tmp->next;
		}
	}
	*lst = NULL;
}
