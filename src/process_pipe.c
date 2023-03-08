/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/18 15:28:59 by tmercier      #+#    #+#                 */
/*   Updated: 2023/02/08 17:46:51 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	create_pipe(t_cmd *c, t_fd *fd)
{
	if (pipe(fd->pip) == -1)
		exit_error("create pipe", 1);
	fd->in = fd->pip[0];
	fd->out = fd->pip[1];
	if (c->rout->len)
		close(fd->pip[1]);
	fd->piped = true;
}

void	fork_process(t_cmdl *cl, t_cmd *c, t_fd *fd)
{
	g_global.pid = fork();
	if (!g_global.pid)
	{
		if (!g_global.is_builtin)
			close(fd->in);
		execute_command(cl, c);
		exit(g_global.exitcode);
	}
	else if (g_global.pid == -1)
		exit_error("fork failed", 1);
}

void	process_pipe(t_cmdl *cl, t_cmd *c, t_fd *fd)
{
	if (c->rin->len)
	{
		fd->in = process_redirin(c, fd);
		if (fd->piped)
			close(fd->pip[0]);
	}
	if (dup2(fd->in, 0) < 0)
		exit_error("recursive - dup2(fd->in, 0)", 1);
	close(fd->in);
	if (c->next)
		create_pipe(c, fd);
	if (c->rout->len)
		fd->out = process_redirout(c, fd);
	else if (!c->next)
		fd->out = dup(fd->tmp[1]);
	if (dup2(fd->out, 1) < 0)
		exit_error("recursive - dup2(fd->out, 1)", 1);
	close(fd->out);
	fork_process(cl, c, fd);
	if (c->next)
		process_pipe(cl, c->next, fd);
}
