/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preppers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 23:34:04 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/19 20:29:52 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_flaginit(void)
{
	g_flags.dash = 0;
	g_flags.zero = 0;
	g_flags.astr = 0;
	g_flags.prec = 0;
	g_flags.neg = 0;
	g_flags.usrdef = 0;
	g_flags.ptr = 0;
	g_flags.pct = 0;
	g_flags.minwidth = 0;
	g_flags.maxwidth = 0;
}

int		ft_intprep(void)
{
	char	*numstr;
	int		num;

	num = va_arg(g_arglst.arg, int);
	if (num < 0)
		g_flags.neg = 1;
	numstr = ft_itoa(num);
	return (ft_intprinter((long long int)num, numstr));
}

int		ft_uintprep(void)
{
	char			*numstr;
	unsigned int	num;

	num = va_arg(g_arglst.arg, unsigned int);
	numstr = ft_llitoa((long long int)num);
	return (ft_intprinter((long long int)num, numstr));
}

int		ft_xintprep(char cs)
{
	char			*numstr;
	unsigned int	num;

	num = va_arg(g_arglst.arg, unsigned int);
	numstr = ft_llitoa_base((long long int)num, 16);
	if (cs == 'x')
		ft_strtolower(numstr);
	return (ft_intprinter((long long int)num, numstr));
}

int		ft_pintprep(void)
{
	char				*numstr;
	char				*del;
	unsigned long int	num;

	num = va_arg(g_arglst.arg, unsigned long int);
	g_flags.ptr = 1;
	if (!num && g_flags.maxwidth == 0 && g_flags.usrdef)
		numstr = ft_strdup("0x");
	else if (num == 18446744073709551615u)
		numstr = ft_strdup("0xffffffffffffffff");
	else
	{
		numstr = ft_llitoa_base((long long int)num, 16);
		del = numstr;
		ft_strtolower(numstr);
		numstr = ft_strjoin("0x", numstr);
		free(del);
	}
	return (ft_intprinter((long long int)num, numstr));
}
