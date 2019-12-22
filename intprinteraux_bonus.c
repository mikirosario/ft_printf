/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intprinteraux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 14:11:31 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/22 14:29:12 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_spacesorhelper(char *str, int strlen, size_t fillwidth)
{
	if (!g_flags.zero || g_flags.usrdef)
		ft_filler(' ', fillwidth);
	if (g_flags.neg)
		write(1, "-", 1);
	if (g_flags.plus || g_flags.sp)
		write(1, (g_flags.plus ? "+" : " "), 1);
	if (g_flags.zero && !g_flags.usrdef)
		ft_filler('0', fillwidth);
	ft_putstr((g_flags.neg || g_flags.plus || \
			g_flags.sp ? &str[1] : str), strlen);
}

void	ft_spacesandhelper(char *str, int strlen, int fillwidth)
{
	ft_filler(' ', fillwidth);
	if (g_flags.neg)
		write(1, "-", 1);
	if (g_flags.plus || g_flags.sp)
		write(1, (g_flags.plus ? "+" : " "), 1);
	ft_filler('0', (g_flags.maxwidth - strlen));
	ft_putstr((g_flags.neg || g_flags.plus || \
				g_flags.sp ? &str[1] : str), strlen);
}
