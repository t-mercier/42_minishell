/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _ft_printf.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 11:56:22 by asaijers      #+#    #+#                 */
/*   Updated: 2023/03/02 13:44:54 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/_types/_va_list.h>
# include <unistd.h>

typedef int	(*t_f_)(va_list vl);

/*					ft_printf.c
** ------------------------------------------ */
int			ft_printf(const char *fmt, ...);

/*					ft_printf2.c
** ------------------------------------------ */
int			_printf_hex(va_list vl);
int			_printf_hexupper(va_list vl);
int			_printf_dec(va_list vl);
int			_printf_unsigned(va_list vl);
int			ft_vprintf(const char *fmt, va_list vl);

/*					ft_printf3.c
** ------------------------------------------ */
int			_printf_char(va_list vl);
int			_printf_putstr(char *s);
int			_printf_str(va_list vl);
int			_printf_ptr(va_list vl);
int			_printf_call(char c, va_list vl);

/*					ft_printf4.c
** ------------------------------------------ */
size_t		_printf_strlen(const char *s);
void		*_printf_memcpy(void *dst, const void *src, size_t n);
char		*_printf_strdup(char *s);
char		*_printf_sltoa(long n, int o, char *base);
char		*_printf_ultoa(unsigned long n, char *base);

#endif
