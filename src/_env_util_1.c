/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envutil.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 16:21:31 by asaijers      #+#    #+#                 */
/*   Updated: 2023/02/27 16:37:03 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isenvkey(char *k)
{
	if (!*k || (!ft_isalpha(*k) && *k != '_'))
		return (0);
	k++;
	while (*k && *k != '=')
	{
		if (!ft_isalnum(*k) && *k != '_')
			return (0);
		k++;
	}
	return (1);
}

int	isenv(int c)
{
	return (c == '_' || ft_isalnum(c));
}

char	*env_val_escape(char *s)
{
	t_vector	*v;
	char		*q;

	v = ft_vector_create(sizeof(char));
	while (*s)
	{
		if (*s == '"' || *s == '$')
			ft_vector_push(v, "\\");
		ft_vector_push(v, s++);
	}
	ft_vector_push(v, "");
	q = ft_strdup(v->data);
	ft_vector_destroy(v);
	return (q);
}
