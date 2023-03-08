/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mem.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:10:37 by asaijers      #+#    #+#                 */
/*   Updated: 2022/10/14 11:52:42 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*a;
	const char	*b;

	if (!dst && !src)
		return (0);
	a = dst;
	b = src;
	while (n--)
		a[n] = b[n];
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == src)
		return (dst);
	if (src > dst && src - dst < (int)n)
	{
		i = 0;
		while (i < n)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
		return (dst);
	}
	return (ft_memcpy(dst, src, n));
}

void	*ft_memset(void *s, int c, size_t n)
{
	char	*a;

	a = s;
	while (n--)
		a[n] = c;
	return (s);
}

void	*ft_memchr(void *s, int c, size_t n)
{
	unsigned char	*a;

	a = s;
	while (n--)
	{
		if (*a == (unsigned char)c)
			return (a);
		a++;
	}
	return (0);
}

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;

	a = s1;
	b = s2;
	while (n)
	{
		if (*a != *b)
			break ;
		a++;
		b++;
		n--;
	}
	if (!n)
		return (0);
	return (*a - *b);
}
