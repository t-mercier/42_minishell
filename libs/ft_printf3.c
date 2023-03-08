/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   a.c                                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 11:03:06 by asaijers      #+#    #+#                 */
/*   Updated: 2022/11/07 11:17:29 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"

int	_printf_char(va_list vl)
{
	char	c;

	c = va_arg(vl, int);
	write(STDOUT_FILENO, &c, 1);
	return (1);
}

int	_printf_putstr(char *s)
{
	return ((int)write(STDOUT_FILENO, s, _printf_strlen(s)));
}

int	_printf_str(va_list vl)
{
	char	*s;

	s = va_arg(vl, char *);
	if (!s)
		return (_printf_putstr("(null)"));
	return (_printf_putstr(s));
}

int	_printf_ptr(va_list vl)
{
	char	*s;
	int		n;

	s = _printf_ultoa((intptr_t)va_arg(vl, void *), "0123456789abcdef");
	n = _printf_putstr("0x");
	n += _printf_putstr(s);
	free(s);
	return (n);
}

int	_printf_call(char c, va_list vl)
{
	t_f_		ff;
	static t_f_	g_f[INT8_MAX];

	g_f['x'] = _printf_hex;
	g_f['X'] = _printf_hexupper;
	g_f['d'] = _printf_dec;
	g_f['i'] = _printf_dec;
	g_f['p'] = _printf_ptr;
	g_f['s'] = _printf_str;
	g_f['c'] = _printf_char;
	g_f['u'] = _printf_unsigned;
	ff = g_f[(int)c];
	if (ff)
		return (ff(vl));
	return (0);
}
