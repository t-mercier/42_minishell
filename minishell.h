/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmercier <tmercier@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/03 18:53:34 by tmercier      #+#    #+#                 */
/*   Updated: 2023/02/28 17:39:19 by asaijers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs/_libft.h"
# include "libs/lib42.h"
# include "zzz.h"
# include <dirent.h>
# include <pwd.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <sys/fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <uuid/uuid.h>

# define BUILTINLEN 7
# ifndef PROMPT
#  define PROMPT "💀 "
# endif

/* EXECUTION */
typedef struct s_cmdl	t_cmdl;
typedef struct s_cmd	t_cmd;
typedef struct s_fd		t_fd;
typedef struct s_ro		t_ro;
typedef struct s_ri		t_ri;
typedef struct s_path	t_path;

struct					s_fd
{
	int					in;
	int					out;
	int					tmp[2];
	int					pip[2];
	bool				piped;
};

struct					s_path
{
	t_vector			*v_path;
	char				**tab;
	char				*dir;
	char				*path;
	char				*cmd;
};

typedef struct s_ff
{
	int					m[2];
	int					std[2];
	int					ppip[2];
	int					pip[2];
}						t_ff;

typedef void			(*t_builtin_f)(t_cmdl *cl, t_cmd *c);

typedef struct s_builtin
{
	char				*name;
	t_builtin_f			func;
	int					fork;
}						t_builtin;

enum					e_TOKEN_TYPE
{
	_TK_INVALID,
	_TK_ERROR,
	TK_ID,
	TK_PIPE,
	TK_BT,
	TK_LT,
	TK_DBT,
	TK_DLT,
	TK_DOLLAR,
	TK_LP,
	TK_RP,
	TK_Q,
	TK_SQ,
	TK_DQ,
	TK_STR,
	_TK_LEN
};

typedef struct s_token
{
	char				*val;
	enum e_TOKEN_TYPE	type;
}						t_token;

typedef struct s_parser
{
	char				*b;
	int					c;
	int					l;
	int					table[255];
	int					xt[_TK_LEN];
	int					err;
	t_vector			*env;
}						t_parser;

typedef struct s_env
{
	char				*env_var;
}						t_env;

struct					s_ro
{
	char				*file;
	char				is_append;
};

struct					s_ri
{
	char				*file;
	char				is_delim;
};

struct					s_cmd
{
	t_vector			*args;
	t_cmd				*next;
	t_vector			*rout;
	t_vector			*rin;
};

struct					s_cmdl
{
	t_vector			*env;
	t_cmd				*head;
};

struct					s_global
{
	int					pid;
	int					ppid;
	int					busy;
	int					exitcode;
	bool				is_builtin;
	t_builtin			builtins[BUILTINLEN];
};

extern struct s_global	g_global;

/* _env_util_1.c */
char					*env_val_escape(char *s);
int						isenv(int c);
int						isenvkey(char *k);

/* _env_util_2.c */
void					_unsetenv(t_vector *env, char *key);
char					*_getenv(t_vector *env, char *key);
void					_setenv(t_vector *env, char *key, char *val);

/* _errors.c */
void					exit_error(char *msg, int code);
void					message_error(char *msg);
char					*env_val_escape(char *s);

/* _parse_util.c */
char					q(t_parser *p);
char					*qq(t_parser *p);
int						ft_isquote(int c);
int						_isdelim(int c);
void					str_tolower(char *s);

/* _path_util.c */
t_vector				*path_vector(t_vector *v, char *d, char *cmd);
t_path					*path_construct(DIR *curr, t_path *p);
t_path					*path_dir(t_path *p, DIR *curr, struct dirent *s_dir);

/* builtin_1.c */
void					builtin_exit(t_cmdl *cl, t_cmd *c);
void					builtin_echo(t_cmdl *cl, t_cmd *c);
t_builtin				get_builtin(t_cmd *c);

/* builtin_2.c */
void					builtin_export(t_cmdl *cl, t_cmd *c);

/* builtin_3.c */
void					builtin_unset(t_cmdl *cl, t_cmd *c);
void					builtin_env(t_cmdl *cl, t_cmd *c);
void					builtin_cd(t_cmdl *cl, t_cmd *c);
void					builtin_pwd(t_cmdl *cl, t_cmd *c);

/* parse_cmd_1.c */
t_cmdl					*get_cmdl(t_parser *p);
t_cmd					*get_cmd(t_parser *p);
int						redir(t_parser *p, t_cmd *c, t_token t);

/* parse_cmd_2.c */
void					cmdl_print(t_cmdl *cl);
void					cmd_destroy(t_cmd *c);
t_cmd					*cmd(void);

/* parse_exp.c */
char					*_expand(t_parser *p, char *a);
char					*_expand_env(t_parser *p, char *a, t_vector *r);
char					*_expand_fisrt(t_parser *p, char *a);
t_cmdl					*parse(char *k, t_vector *env);

/* process_cmd.c */
void					execute_command(t_cmdl *cl, t_cmd *c);
void					restore_std(t_fd *fd);
void					process_simple(t_cmdl *cl, t_cmd *c, t_fd *fd);
void					process_pipeline(t_cmdl *cl, t_fd *fd);

/* process_cmdl.c */
void					process_execution(t_cmdl *cl);
void					process_fd(t_cmdl *cl, t_fd *fd);

/* process_env.c */
t_vector				*build_env(char **envp);

/* process_path.c */
char					*build_path(t_cmdl *cl, t_cmd *cmd);
char					*process_path(t_cmdl *cl, t_cmd *c);

/* process_pipe.c */
void					process_pipe(t_cmdl *cl, t_cmd *c, t_fd *fd);

/* process_redirections.c */
int						process_redirin(t_cmd *c, t_fd *fd);
int						process_redirout(t_cmd *c, t_fd *fd);

/* process_signals.c */
void					sigint_handler(int sig);
void					sigquit_handler(int sig);
void					setup_signals(void);

/* token.c */
const char				*token_name(int type);
t_token					tk(int type, char *v);
char					*token_str(t_parser *p);
t_token					token_id(t_parser *p);
t_token					token(t_parser *p);
t_token					_token(t_parser *p);

/* orun.c */
int						run(t_cmdl *cl);
void					e_rout(t_cmdl *cl, t_cmd *c, t_ff *f);
void					e_rin(t_cmdl *cl, t_cmd *c, t_ff *f);
void					e_pipe(t_cmdl *cl, t_cmd *c, t_ff *f);
char					*_getenv(t_vector *env, char *key);
void					_unsetenv(t_vector *env, char *key);
void					_setenv(t_vector *env, char *key, char *val);
#endif
