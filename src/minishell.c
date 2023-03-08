/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 21:29:16 by tmercier      #+#    #+#                 */
/*   Updated: 2023/03/02 17:34:22 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stddef.h>
#include <stdlib.h>

struct s_global	g_global;

void	dashc(char **argv)
{
	t_cmdl	*cl;

	if (!argv[2][0])
		exit(0);
	cl = parse(argv[2], 0);
	if (!cl || !cl->head)
	{
		perror("Error");
		exit(g_global.exitcode);
	}
	process_execution(cl);
	exit(g_global.exitcode);
}

void	init_builtins(void)
{
	g_global.builtins[0] = (t_builtin){"echo", builtin_echo, 1};
	g_global.builtins[1] = (t_builtin){"cd", builtin_cd, 0};
	g_global.builtins[2] = (t_builtin){"export", builtin_export, 0};
	g_global.builtins[3] = (t_builtin){"env", builtin_env, 1};
	g_global.builtins[4] = (t_builtin){"exit", builtin_exit, 0};
	g_global.builtins[5] = (t_builtin){"pwd", builtin_pwd, 1};
	g_global.builtins[6] = (t_builtin){"unset", builtin_unset, 0};
}

static int	next(t_vector *env)
{
	t_cmdl	*cl;
	char	*line;

	g_global.busy = 0;
	line = readline(PROMPT);
	g_global.busy = 1;
	if (!line)
		return (1);
	if (!line[0])
	{
		free(line);
		return (0);
	}
	cl = parse(line, env);
	if (cl == 0 || !cl->head)
		return (message_error("bad command"), free(line), 0);
	cl->env = env;
	process_execution(cl);
	add_history(line);
	cmd_destroy(cl->head);
	free(cl);
	free(line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_vector	*env;
	size_t		i;

	if (argc == 3 && argv[1][1] == 'c')
		dashc(argv);
	setup_signals();
	init_builtins();
	env = build_env(envp);
	while (!next(env))
		;
	i = 0;
	while (i < env->len)
		free(*(char **)ft_vector_get(env, i++));
	ft_vector_destroy(env);
	return (g_global.exitcode);
}
