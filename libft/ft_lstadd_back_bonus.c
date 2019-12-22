/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 22:32:32 by mrosario          #+#    #+#             */
/*   Updated: 2019/11/19 19:03:13 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (!new)
		return ;
	if (alst && *alst)
	{
		new->next = (ft_lstlast(*alst))->next;
		(ft_lstlast(*alst))->next = new;
	}
	else
	{
		*alst = new;
		new->next = NULL;
	}
}
