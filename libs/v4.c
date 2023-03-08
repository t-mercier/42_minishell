/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   v4.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 13:44:07 by asaijers      #+#    #+#                 */
/*   Updated: 2023/03/02 13:44:09 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"
#include <stddef.h>

void	*ft_vector_delfast(t_vector *v, size_t i)
{
	if (i < 0 || i >= v->len)
		return (0);
	ft_vector_swap(v, i, v->len - 1);
	return (ft_vector_pop(v));
}
