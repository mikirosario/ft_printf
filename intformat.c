/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intformat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 06:37:17 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/22 08:18:04 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

long long int	ft_intextract(void)
{
	long long int	num;

	if (g_lenspec.l)
		num = va_arg(g_arglst.arg, long int);
	else if (g_lenspec.ll)
		num = va_arg(g_arglst.arg, long long int);
	else
		num = va_arg(g_arglst.arg, int);
	return (num);
}

char			*ft_intwrite(long long int num)
{
	char	*numstr;

	if (g_lenspec.hh)
		numstr = ft_itoa((char)num);
	else if (g_lenspec.h)
		numstr = ft_itoa((short)num);
	else if (g_lenspec.l)
		numstr = ft_llitoa((long long int)num);
	else if (g_lenspec.ll)
		numstr = ft_llitoa(num);
	else
		numstr = ft_itoa((int)num);
	return (numstr);
}

char			*ft_numstrprep(char *numstr)
{
	char	*del;

	if (g_flags.apos)
	{
		del = numstr;
		numstr = ft_thousep(numstr, ',');
		free(del);
	}
	if (g_flags.plus || g_flags.sp)
	{
		del = numstr;
		numstr = ft_strjoin((g_flags.plus ? "+" : " "), numstr);
		free(del);
	}
	return (numstr);
}
