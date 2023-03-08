/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   v3.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 14:49:28 by asaijers      #+#    #+#                 */
/*   Updated: 2023/03/02 13:43:35 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "_libft.h"

ssize_t	ft_vector_indexof(t_vector *v, void *e, t_f_compare cmp)
{
	size_t	i;

	i = 0;
	while (i < v->len)
	{
		if (cmp(ft_vector_get(v, i), e) == 0)
			return (i);
		i++;
	}
	return (-1);
}

// add n * v.esz bytes of d to the end of v
void	ft_vector_concat(t_vector *v, void *d, size_t n)
{
	ft_vector_grow(v, n);
	ft_memcpy(v->data + v->len * v->esz, d, n * v->esz);
	v->len += n;
}

t_vector	*ft_vec_concat_str(t_vector *v, char *s)
{
	if (v->len > 0 && !*(char *)ft_vector_get(v, v->len - 1))
		ft_vector_pop(v);
	ft_vector_concat(v, s, ft_strlen(s));
	ft_vector_push(v, &(char){0});
	return (v);
}

void	ft_vector_destroy(t_vector *v)
{
	free(v->data);
	free(v);
}

void	*ft_vector_set(t_vector *v, size_t i, void *el)
{
	return (ft_memcpy(v->data + i * v->esz, el, v->esz));
}
