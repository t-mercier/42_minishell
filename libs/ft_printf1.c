/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 14:55:47 by asaijers      #+#    #+#                 */
/*   Updated: 2022/11/29 14:56:49 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_ft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	va_list	v;
	int		n;

	va_start(v, fmt);
	n = ft_vprintf(fmt, v);
	va_end(v);
	return (n);
}
