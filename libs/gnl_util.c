/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 12:23:55 by asaijers      #+#    #+#                 */
/*   Updated: 2022/11/02 13:40:24 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_gnl.h"
#include <stdlib.h>

void	*_gnl_memcpy(void *dst, void *src, size_t n)
{
	char	*a;
	char	*b;

	a = dst;
	b = src;
	while (n--)
		a[n] = b[n];
	return (dst);
}

size_t	_gnl_strlen(const char *s)
{
	const char	*a;

	if (!s)
		return (0);
	a = s;
	while (*s)
		s++;
	return (s - a);
}

void	*_gnl_fake_realloc(void *p, size_t on, size_t n)
{
	void	*a;

	if (!p)
		return (malloc(n));
	a = malloc(n);
	if (!a)
	{
		free(p);
		return (0);
	}
	_gnl_memcpy(a, p, on);
	free(p);
	return (a);
}
