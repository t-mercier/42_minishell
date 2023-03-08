/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 12:09:38 by asaijers      #+#    #+#                 */
/*   Updated: 2022/10/11 14:59:15 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

int	ft_isprint(int c)
{
	return (32 <= c && c < 127);
}

int	ft_isascii(int c)
{
	return (0 <= c && c <= 127);
}

int	ft_isspace(int c)
{
	return ((9 <= c && c <= 13) || c == 32);
}
