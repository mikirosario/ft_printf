/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charformat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 08:52:13 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/22 14:15:08 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

wint_t	ft_charextract(void)
{
	wint_t	wc;

	if (g_flags.pct)
		wc = '%';
	else if (g_lenspec.l)
		wc = va_arg(g_arglst.arg, wint_t);
	else
		wc = va_arg(g_arglst.arg, int);
	return (wc);
}

char	*ft_strextract(void)
{
	char *str;

	if (g_flags.prec && g_flags.usrdef && !g_flags.maxwidth)
	{
		str = "";
		va_arg(g_arglst.arg, char *);
	}
	else if (!(str = va_arg(g_arglst.arg, char *)))
		str = "(null)";
	return (str);
}

wchar_t	*ft_wstrextract(void)
{
	wchar_t *str;

	if (g_flags.prec && g_flags.usrdef && !g_flags.maxwidth)
	{
		str = (wchar_t *)"";
		va_arg(g_arglst.arg, wchar_t *);
	}
	else if (!(str = va_arg(g_arglst.arg, wchar_t *)))
		str = (wchar_t *)"(null)";
	return (str);
}
