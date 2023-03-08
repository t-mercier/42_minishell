/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   v2.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 16:10:40 by asaijers      #+#    #+#                 */
/*   Updated: 2023/03/02 13:43:33 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

void	*ft_vector_push(t_vector *v, void *el)
{
	ft_vector_grow(v, 1);
	return (ft_memcpy(v->data + (v->len++) * v->esz, el, v->esz));
}

void	*ft_vector_pop(t_vector *v)
{
	return (v->data + --v->len * v->esz);
}

void	ft_vector_swap(t_vector *v, int a, int b)
{
	void	*t;

	t = malloc(v->esz);
	ft_memcpy(t, ft_vector_get(v, a), v->esz);
	ft_memcpy(ft_vector_get(v, a), ft_vector_get(v, b), v->esz);
	ft_memcpy(ft_vector_get(v, b), t, v->esz);
	free(t);
}

t_vector	*ft_vector_copy(t_vector *v)
{
	t_vector	*n;

	n = ft_vector_create(v->esz);
	ft_vector_grow(n, v->cap);
	n->len = v->len;
	ft_memcpy(n->data, v->data, v->len * v->esz);
	return (n);
}

void	*ft_vector_get(t_vector *v, int i)
{
	return (v->data + i * v->esz);
}
