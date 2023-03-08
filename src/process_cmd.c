/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 20:15:44 by tmercier      #+#    #+#                 */
/*   Updated: 2023/03/06 11:23:19 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	restore_std(t_fd *fd)
{
	if (dup2(fd->tmp[1], 1) < 0)
		exit_error("dup fd before processing pipe", 1);
	if (dup2(fd->tmp[0], 0) < 0)
		exit_error("dup fd before processing pipe", 1);
	close(fd->tmp[0]);
	close(fd->tmp[1]);
}

void	update_env(t_cmdl *cl, char *p)
{
	char	*tmp;
	int		n;
	char	*new;

	_setenv(cl->env, "_", p);
	tmp = _getenv(cl->env, "SHLVL");
	if (!tmp)
		n = 0;
	else
		n = ft_atoi(tmp);
	new = ft_itoa(++n);
	_setenv(cl->env, "SHLVL", new);
	free(new);
}

void	process_simple(t_cmdl *cl, t_cmd *c, t_fd *fd)
{
	if (!c)
		exit_error("command is null", 1);
	if (c->rin->len || c->rout->len)
		process_fd(cl, fd);
	g_global.pid = fork();
	if (g_global.pid == 0)
	{
		execute_command(cl, c);
		exit(g_global.exitcode);
	}
	else if (g_global.pid < 0)
		exit_error("fork", 128);
	restore_std(fd);
}

void	process_pipeline(t_cmdl *cl, t_fd *fd)
{
	t_builtin	b;

	fd->in = dup(fd->tmp[1]);
	if (cl->head)
	{
		b = get_builtin(cl->head);
		if (b.name)
			g_global.is_builtin = true;
	}
	process_pipe(cl, cl->head, fd);
	restore_std(fd);
}

void	execute_command(t_cmdl *cl, t_cmd *c)
{
	t_builtin	b;
	char		*p;

	b = get_builtin(c);
	if (b.name)
	{
		b.func(cl, c);
		g_global.is_builtin = true;
	}
	else
	{
		g_global.is_builtin = false;
		p = process_path(cl, c);
		ft_vector_push(c->args, &(char *){0});
		ft_vector_push(cl->env, &(char *){0});
		update_env(cl, p);
		if (execve(p, c->args->data, cl->env->data) < 0)
			exit_error("exec", 127);
	}
}
