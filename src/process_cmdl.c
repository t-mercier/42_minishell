/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_cmdl.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 11:31:15 by tmercier      #+#    #+#                 */
/*   Updated: 2023/03/02 14:24:02 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_child(t_cmdl *cl, t_fd *fd)
{
	int	status;

	g_global.ppid = getpid();
	signal(SIGQUIT, sigquit_handler);
	if (!cl->head->next)
		process_simple(cl, cl->head, fd);
	else
		process_pipeline(cl, fd);
	if (g_global.pid)
	{
		waitpid(g_global.pid, &status, 0);
		g_global.exitcode = WEXITSTATUS(status);
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	exit(g_global.exitcode);
}

void	process_fd(t_cmdl *cl, t_fd *fd)
{
	if (cl->head->rin->len)
	{
		fd->in = process_redirin(cl->head, fd);
		dup2(fd->in, 0);
		close(fd->in);
	}
	if (cl->head->rout->len)
	{
		fd->out = process_redirout(cl->head, fd);
		dup2(fd->out, 1);
		close(fd->out);
	}
}

bool	process_builtins(t_cmdl *cl, t_cmd *c, t_fd *fd)
{
	t_builtin	b;

	b = get_builtin(c);
	if (b.name && !b.fork && !c->next)
	{
		if (c->rin->len || c->rout->len)
			process_fd(cl, fd);
		b.func(cl, c);
		restore_std(fd);
		return (true);
	}
	return (false);
}

int	process_fork(t_cmdl *cl, t_fd *fd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		message_error("fork");
		return (1);
	}
	else if (!pid)
		process_child(cl, fd);
	return (pid);
}

void	process_execution(t_cmdl *cl)
{
	t_fd	fd;
	int		status;
	int		pid;

	if (!cl->head)
		return ;
	g_global.pid = 0;
	fd = (t_fd){};
	fd.tmp[0] = dup(0);
	fd.tmp[1] = dup(1);
	if (process_builtins(cl, cl->head, &fd))
		return ;
	pid = process_fork(cl, &fd);
	if (pid)
	{
		waitpid(pid, &status, 0);
		g_global.exitcode = WEXITSTATUS(status);
	}
	close(fd.tmp[0]);
	close(fd.tmp[1]);
}
