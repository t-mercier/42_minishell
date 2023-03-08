/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _env_util_2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 16:58:47 by asaijers      #+#    #+#                 */
/*   Updated: 2023/02/28 17:22:12 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stddef.h>

static int	klen(char *var)
{
	int	vkl;

	if (ft_strchr(var, '='))
		vkl = ft_strchr(var, '=') - var;
	else
		vkl = ft_strlen(var);
	return (vkl);
}

static int	_setenv_loop(t_vector *env, char *key, char *kv)
{
	char	*var;
	int		kl;
	size_t	i;

	i = 0;
	kl = ft_strlen(key);
	while (i < env->len)
	{
		var = *(char **)ft_vector_get(env, i);
		if (klen(var) != kl)
		{
			i++;
			continue ;
		}
		if (!ft_strncmp(key, var, kl))
		{
			free(var);
			ft_vector_set(env, i, &kv);
			return (1);
		}
		i++;
	}
	return (0);
}

void	_setenv(t_vector *env, char *key, char *val)
{
	t_vector	*nkv;
	char		*kv;

	nkv = ft_vector_create(sizeof(char));
	ft_vector_concat(nkv, key, ft_strlen(key));
	if (val)
	{
		ft_vector_push(nkv, "=");
		ft_vector_concat(nkv, val, ft_strlen(val));
	}
	ft_vector_push(nkv, "");
	kv = ft_strdup(nkv->data);
	ft_vector_destroy(nkv);
	if (_setenv_loop(env, key, kv))
		return ;
	ft_vector_push(env, &kv);
}

char	*_getenv(t_vector *env, char *key)
{
	size_t	i;
	int		kl;
	char	*var;
	char	*q;
	int		vkl;

	i = 0;
	kl = ft_strlen(key);
	while (i < env->len)
	{
		var = *(char **)ft_vector_get(env, i++);
		if (!var)
			continue ;
		q = ft_strchr(var, '=');
		if (!q)
			break ;
		vkl = q - var;
		if (kl != vkl)
			continue ;
		if (!ft_strncmp(key, var, kl))
			return (var + vkl + 1);
	}
	return (0);
}

void	_unsetenv(t_vector *env, char *key)
{
	size_t	i;
	int		kl;
	char	*var;

	i = 0;
	kl = ft_strlen(key);
	while (i < env->len)
	{
		var = *(char **)ft_vector_get(env, i);
		if (klen(var) != kl)
		{
			i++;
			continue ;
		}
		if (!ft_strncmp(key, var, kl))
		{
			ft_vector_swap(env, i, env->len - 1);
			free(*(char **)ft_vector_pop(env));
		}
		i++;
	}
}
