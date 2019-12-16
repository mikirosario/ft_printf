/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 02:25:54 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/16 06:17:24 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFTPRINTF_H
# define FT_LIBFTPRINTF_H

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

typedef struct	s_flags
{
	int				dash;
	int				zero;
	int				astr;
	int				prec;
	int				neg;
	long int		minwidth;
	long int		maxwidth;
}				t_flags;

typedef struct	s_arglst
{
	va_list	arg;
}				t_arglst;

unsigned long	g_bytes;
t_flags			g_flags;
t_arglst		g_arglst;

int					ft_printf(char const *format, ...);
char const			*ft_flagparser(char const *format);
int					ft_flagchecker(char	f);
int					ft_widthparser(char const *width);
unsigned long		ft_converter(char cs);
unsigned long		ft_charprinter(void);
unsigned long		ft_strprinter(void);
unsigned long		ft_intprinter(void);
void				ft_foutput(char *str, int strlen, size_t fillwidth);
size_t				ft_onlyspaces(char *str, int strlen, size_t fillwidth);
size_t				ft_onlyzeros(char *str, int strlen);
size_t				ft_spacesandzeros(char *str, int strlen);

// int	ft_minmax(int num);

#endif
