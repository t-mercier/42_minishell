/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_1.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 16:20:56 by tmercier      #+#    #+#                 */
/*   Updated: 2023/03/02 15:32:52 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	isdigits(char *s)
{
	while (*s)
		if (!ft_isdigit(*s++))
			return (0);
	return (1);
}

void	builtin_exit(t_cmdl *cl, t_cmd *c)
{
	unsigned char	i;
	char			*v;
	int				o;

	(void)cl;
	i = g_global.exitcode;
	v = *(char **)ft_vector_get(c->args, 1);
	if (v)
	{
		o = 0;
		if (*v == '-')
			o = 1;
		if (*v == '-' || *v == '+')
			v++;
		if (!isdigits(v) || ft_strlen(v) > 18)
			exit(255);
		if (c->args->len > 2)
			exit(1);
		i = ft_atoi(v);
		if (o)
			i = -i;
	}
	exit(i);
}

static int	_builtin_echo(t_cmd *c, size_t i, int *n)
{
	char	*arg;

	arg = *(char **)ft_vector_get(c->args, i);
	if (!arg)
		return (1);
	if (!n[0] && *arg++ == '-')
	{
		while (*arg == 'n')
			arg++;
		if (!*arg)
		{
			n[1] = 1;
			return (1);
		}
	}
	n[0] = 1;
	return (0);
}

void	builtin_echo(t_cmdl *cl, t_cmd *c)
{
	size_t	i;
	char	*arg;
	int		n[2];

	g_global.exitcode = 0;
	(void)cl;
	i = 0;
	n[0] = 0;
	n[1] = 0;
	while (++i < c->args->len)
	{
		if (_builtin_echo(c, i, n))
			continue ;
		arg = *(char **)ft_vector_get(c->args, i);
		if (ft_strlen(arg))
		{
			ft_printf("%s", arg);
			if (i + 1 < c->args->len)
				ft_printf(" ");
		}
	}
	if (!n[1])
		ft_printf("\n");
}

t_builtin	get_builtin(t_cmd *c)
{
	int			i;
	int			l;
	char		*name;
	t_builtin	b;

	b.fork = 0;
	i = 0;
	l = sizeof(g_global.builtins) / sizeof(g_global.builtins[0]);
	name = *(char **)ft_vector_get(c->args, 0);
	while (i < l)
	{
		b = g_global.builtins[i];
		if (ft_strcmp(b.name, name) == 0)
		{
			return (b);
		}
		i++;
	}
	return ((t_builtin){0});
}
