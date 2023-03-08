/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:10:56 by asaijers      #+#    #+#                 */
/*   Updated: 2022/10/27 21:18:11 by alfa          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

char	*ft_strdup(char *s)
{
	size_t	n;
	void	*d;

	n = ft_strlen(s) + 1;
	d = ft_malloc(n);
	if (!d)
		return (0);
	return (ft_memcpy(d, s, n));
}

char	*ft_strndup(char *s, size_t n)
{
	char	*a;

	a = malloc(n + 1);
	if (!a)
		return (0);
	ft_memcpy(a, s, n);
	a[n] = 0;
	return (a);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	sl;

	sl = ft_strlen(src);
	if (!n)
		return (sl);
	while (n-- > 1 && *src)
		*dst++ = *src++;
	*dst = 0;
	return (sl);
}

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	dl;
	size_t	sl;

	dl = ft_strnlen(dst, n);
	sl = ft_strlen(src);
	if (dl == n)
		return (n + ft_strlen(src));
	if (sl < n - dl)
	{
		ft_memcpy(dst + dl, src, sl + 1);
	}
	else
	{
		ft_memcpy(dst + dl, src, n - dl - 1);
		dst[n - 1] = 0;
	}
	return (sl + dl);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	char	*r;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	r = ft_malloc(l1 + l2 + 1);
	if (!r)
		return (0);
	ft_memcpy(r, (void *)s1, l1);
	ft_memcpy(r + l1, (void *)s2, l2);
	r[l1 + l2] = 0;
	return (r);
}
