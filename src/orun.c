/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   orun.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: asaijers <asaijers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 13:19:22 by asaijers      #+#    #+#                 */
/*   Updated: 2023/03/02 15:38:33 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static int	pb(t_cmdl *cl, t_cmd *c, t_ff *f)
{
	t_builtin	b;

	b = get_builtin(c);
	if (b.name && !cl->head->next)
	{
		f->std[0] = f->m[0];
		f->std[1] = f->m[1];
		e_rin(cl, c, f);
		e_rout(cl, c, f);
		dup2(f->std[0], 0);
		dup2(f->std[1], 1);
		b.func(cl, c);
		return (1);
	}
	return (0);
}

static void	child(t_cmdl *cl, t_cmd *c, t_ff *f)
{
	char		*p;
	char		*a1;
	t_builtin	b;

	b = get_builtin(c);
	f->std[0] = f->m[0];
	f->std[1] = f->m[1];
	e_pipe(cl, c, f);
	e_rin(cl, c, f);
	e_rout(cl, c, f);
	dup2(f->std[0], 0);
	dup2(f->std[1], 1);
	if (!b.name)
	{
		ft_vector_push(c->args, &(char *){0});
		ft_vector_push(cl->env, &(char *){0});
		p = process_path(cl, c);
		a1 = *(char **)ft_vector_get(c->args, 0);
		if (a1[0] == '.')
			p = a1;
		if (execve(p, c->args->data, cl->env->data) < 0)
			exit_error("exec", 127);
	}
	b.func(cl, c);
	exit(g_global.exitcode);
}

static int	runcmd(t_cmdl *cl, t_cmd *c, t_ff *f)
{
	if (pb(cl, c, f))
		return (1);
	if (c->next)
		pipe(f->pip);
	g_global.pid = fork();
	if (!g_global.pid)
		child(cl, c, f);
	if (g_global.pid < 0)
	{
		message_error("fork");
		g_global.exitcode = 128;
		return (1);
	}
	close(f->ppip[0]);
	close(f->ppip[1]);
	f->ppip[0] = f->pip[0];
	f->ppip[1] = f->pip[1];
	return (0);
}

static void	_run(t_cmdl *cl, t_cmd *c, t_ff *f)
{
	int	status;

	while (c)
	{
		if (runcmd(cl, c, f))
			break ;
		c = c->next;
	}
	if (g_global.pid > 0)
	{
		waitpid(g_global.pid, &status, 0);
		g_global.exitcode = WEXITSTATUS(status);
	}
	while (waitpid(-1, 0, 0) >= 0)
		;
}

int	run(t_cmdl *cl)
{
	extern char	**environ;
	t_cmd		*c;
	int			ostd[2];
	t_ff		f;

	c = cl->head;
	g_global.pid = 0;
	f = (t_ff){0};
	ostd[0] = dup(0);
	ostd[1] = dup(1);
	f.m[0] = dup(0);
	f.m[1] = dup(0);
	f.ppip[0] = -1;
	f.ppip[1] = -1;
	_run(cl, c, &f);
	close(f.m[0]);
	close(f.m[1]);
	dup2(ostd[0], 0);
	dup2(ostd[1], 1);
	close(ostd[0]);
	close(ostd[1]);
	return (0);
}
