/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_3.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 16:34:50 by asaijers      #+#    #+#                 */
/*   Updated: 2023/03/06 11:50:41 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stddef.h>
#include <unistd.h>

void	builtin_pwd(t_cmdl *cl, t_cmd *c)
{
	char	*path;

	(void)c;
	(void)cl;
	g_global.exitcode = 0;
	path = getcwd(0, 0);
	ft_printf("%s\n", path);
	free(path);
}

char	*_builtin_cd1(t_cmdl *cl, t_cmd *c)
{
	char	*path;

	if (c->args->len > 1)
		path = *(char **)ft_vector_get(c->args, 1);
	else
		path = _getenv(cl->env, "HOME");
	return (path);
}

void	builtin_cd(t_cmdl *cl, t_cmd *c)
{
	char	*path;
	int		code;
	DIR		*dir;

	path = _builtin_cd1(cl, c);
	if (!path)
	{
		message_error("cd: invalid path");
		return ((void)(g_global.exitcode = 1));
	}
	_setenv(cl->env, "OLDPWD", _getenv(cl->env, "PWD"));
	dir = opendir(path);
	if (!dir)
	{
		message_error("cd: not a directory");
		return ((void)(g_global.exitcode = 1));
	}
	closedir(dir);
	code = chdir(path);
	path = getcwd(0, 0);
	_setenv(cl->env, "PWD", path);
	free(path);
	if (code)
		g_global.exitcode = 1;
}

void	builtin_env(t_cmdl *cl, t_cmd *c)
{
	size_t	i;
	char	*var;

	(void)c;
	i = 0;
	g_global.exitcode = 0;
	while (i < cl->env->len)
	{
		var = *(char **)ft_vector_get(cl->env, i++);
		if (ft_strchr(var, '='))
			ft_printf("%s\n", var);
	}
}

void	builtin_unset(t_cmdl *cl, t_cmd *c)
{
	char	*var;
	size_t	i;

	i = 1;
	g_global.exitcode = 0;
	while (i < c->args->len)
	{
		var = *(char **)ft_vector_get(c->args, i++);
		if (!var)
			continue ;
		if (*var == '-')
		{
			g_global.exitcode = 2;
			message_error("unset : invalid option");
			continue ;
		}
		if (!isenvkey(var))
		{
			g_global.exitcode = 1;
			message_error("unset : invalid identifier");
			continue ;
		}
		_unsetenv(cl->env, var);
	}
}
