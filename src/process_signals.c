/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 19:07:24 by tmercier      #+#    #+#                 */
/*   Updated: 2023/02/27 12:06:49 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	ft_putstr_fd("\n", 2);
	if (!g_global.busy)
		rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	sigquit_handler(int sig)
{
	if (g_global.ppid == getpid())
		ft_printf("Quit: %d\n", sig);
	exit(131);
}

void	setup_signals(void)
{
	rl_event_hook = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
