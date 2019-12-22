/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uintformat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 06:45:27 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/22 13:46:09 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

unsigned long long int	ft_uintextract(void)
{
	unsigned long long int num;

	if (g_lenspec.l)
		num = va_arg(g_arglst.arg, unsigned long int);
	else if (g_lenspec.ll)
		num = va_arg(g_arglst.arg, unsigned long long int);
	else
		num = va_arg(g_arglst.arg, unsigned int);
	return (num);
}

char					*ft_uintwrite(unsigned long long int num)
{
	char	*numstr;

	if (g_lenspec.hh)
		numstr = ft_lluitoa((unsigned char)num);
	else if (g_lenspec.h)
		numstr = ft_lluitoa((unsigned short)num);
	else if (g_lenspec.l)
		numstr = ft_lluitoa((unsigned long int)num);
	else if (g_lenspec.ll)
		numstr = ft_lluitoa(num);
	else
		numstr = ft_lluitoa((unsigned int)num);
	return (numstr);
}

char					*ft_unumstrprep(char *numstr)
{
	char	*del;

	if (g_flags.apos)
	{
		del = numstr;
		numstr = ft_thousep(numstr, ',');
		free(del);
	}
	return (numstr);
}

char					*ft_xintwrite(unsigned long long int num)
{
	char	*numstr;

	if (g_lenspec.hh)
		numstr = ft_lluitoa_base((unsigned char)num, 16);
	else if (g_lenspec.h)
		numstr = ft_lluitoa_base((unsigned short)num, 16);
	else if (g_lenspec.l)
		numstr = ft_lluitoa_base((unsigned long int)num, 16);
	else if (g_lenspec.ll)
		numstr = ft_lluitoa_base(num, 16);
	else
		numstr = ft_lluitoa_base((unsigned int)num, 16);
	return (numstr);
}

char					*ft_xintprefixhandler(unsigned long long int n, char c)
{
	char *numstr;
	char *del;

	if (g_flags.hash)
	{
		numstr = ft_xintwrite(n);
		del = numstr;
		if (c == 'x')
			ft_strtolower(numstr);
		numstr = ft_strjoin((c == 'x' ? "0x" : "0X"), numstr);
		free(del);
	}
	else
	{
		numstr = ft_xintwrite(n);
		if (c == 'x')
			ft_strtolower(numstr);
	}
	return (numstr);
}
