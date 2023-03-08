/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:09:07 by asaijers      #+#    #+#                 */
/*   Updated: 2022/10/14 12:15:21 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

#ifndef LIBFT_NO_MALLOC

void	*ft_malloc(size_t n)
{
	return (malloc(n));
}
#endif

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*a;

	a = ft_malloc(nmemb * size);
	if (!a)
		return (0);
	ft_bzero(a, nmemb * size);
	return (a);
}
