/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/12 20:39:21 by tmercier      #+#    #+#                 */
/*   Updated: 2023/02/12 20:39:21 by tmercier      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	message_error(char *msg)
{
	ft_putstr_fd("\e[31;1m😡 \e[31m", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putendl_fd("\e[m", STDERR_FILENO);
}

void	exit_error(char *msg, int code)
{
	message_error(msg);
	g_global.exitcode = code;
	exit(code);
}
//
//void	error(char *msg, int code)
//{
//	message_perror(msg);
//	g_global.exitcode = code;
//}
