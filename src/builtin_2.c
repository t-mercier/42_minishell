/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/30 16:59:13 by tmercier      #+#    #+#                 */
/*   Updated: 2023/03/02 15:32:29 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fexit(int c)
{
	g_global.exitcode = c;
}

void	_builtin_export1(t_cmdl *cl, char *a)
{
	char	*b;
	char	*d;

	if (a[0] == '-')
	{
		message_error("export: invalid option");
		fexit(2);
		return ;
	}
	if (!isenvkey(a))
	{
		message_error("export: invalid identifier");
		fexit(1);
		return ;
	}
	b = ft_strchr(a, '=');
	if (!b && !_getenv(cl->env, a))
		_setenv(cl->env, a, 0);
	else if (b)
	{
		d = ft_strndup(a, b - a);
		_setenv(cl->env, d, b + 1);
		free(d);
	}
}

void	_builtin_export2(t_cmdl *cl)
{
	char	*v;
	char	*v2;
	char	*val;
	size_t	i;
	char	*d;

	i = 0;
	while (i < cl->env->len)
	{
		v = *(char **)ft_vector_get(cl->env, i++);
		v2 = ft_strchr(v, '=');
		if (v2)
		{
			d = ft_strndup(v, v2 - v);
			val = env_val_escape(v2 + 1);
			ft_printf("declare -x %s=\"%s\"\n", d, val);
			free(d);
			free(val);
		}
		else
			ft_printf("declare -x %s\n", v);
	}
}

void	builtin_export(t_cmdl *cl, t_cmd *c)
{
	char	*a;
	size_t	i;

	g_global.exitcode = 0;
	if (c->args->len > 1)
	{
		i = 1;
		while (i < c->args->len)
		{
			a = *(char **)ft_vector_get(c->args, i++);
			if (!a)
				break ;
			_builtin_export1(cl, a);
		}
	}
	else
		_builtin_export2(cl);
}
