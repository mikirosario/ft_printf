/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 02:25:54 by mrosario          #+#    #+#             */
/*   Updated: 2019/12/20 23:05:59 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFTPRINTF_H
# define FT_LIBFTPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct		s_flags
{
	int				dash;
	int				zero;
	int				astr;
	int				prec;
	int				neg;
	int				hash;
	int				plus;
	int				sp;
	int				apos;
	int				usrdef;
	int				ptr;
	int				pct;
	int				minwidth;
	int				maxwidth;
}					t_flags;

typedef struct		s_arglst
{
	va_list	arg;
}					t_arglst;

int					g_bytes;
t_flags				g_flags;
t_arglst			g_arglst;

int					ft_printf(char const *format, ...);
void				ft_flaginit(void);
char const			*ft_flagparser(char const *format);
void				ft_flagchecker(char	f);
int					ft_widthparser(char const *format);
void				ft_argwidthflags(char const *format);
int					ft_converter(char cs);
int					ft_intprep(void);
int					ft_uintprep(void);
int					ft_xintprep(char cs);
int					ft_pintprep(char cs);
int					ft_charprinter(void);
int					ft_strprinter(void);
void				ft_foutput(char *str, int strlen, size_t fillwidth);
int					ft_intprinter(long long int num, char *numstr);
int					ft_spacesorzeros(char *str, int strlen, size_t fillwidth);
int					ft_onlyzeros(char *str, int strlen);
int					ft_spacesandzeros(char *str, int strlen);
int					ft_xintprinter(long long int num, char *numstr, char cs);
int					ft_hexspacesorzeros(char *str, int strlen, size_t fillwidth, char cs);
int					ft_hexonlyzeros(char *str, int strlen, char cs);
int					ft_hexspacesandzeros(char *str, int strlen, char cs);

#endif
