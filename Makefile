# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: asaijers <asaijers@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/03/02 13:48:12 by asaijers      #+#    #+#                  #
#    Updated: 2023/03/02 13:48:14 by asaijers      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #



CFLAGS += -g3 -I. -I${HOMEBREW_HOME}/opt/readline/include
CFLAGS += -fsanitize=address
CFLAGS += -Werror -Wall -Wextra

SRCS 	=  	_env_util_1.c     _parse_util.c     builtin_2.c       orun.c \
			parse_cmd_2.c     process_cmdl.c    process_pipe.c    token_1.c \
			_env_util_2.c     _path_util.c      builtin_3.c       orun2.c \
			parse_exp.c       process_env.c     process_rd.c      token_2.c \
			_errors.c         builtin_1.c       minishell.c       parse_cmd_1.c \
			process_cmd.c     process_path.c    process_signals.c

OBJS 	=	$(addprefix out/, $(SRCS:.c=.o))
BIN 	= 	minishell
LFLAGS 	+= 	-lreadline -L${HOMEBREW_HOME}/opt/readline/lib
CC 		= 	clang

$(shell mkdir -p out)

all: $(BIN)
	$(MAKE) -C libs

$(BIN): $(OBJS) libs/lib42.a
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

out/%.o: src/%.c minishell.h
	@printf "$(GREEN)Compiling: $(RESET)$(notdir $<)\n"
	$(CC) $(CFLAGS) -c -o $@ $<

libs/lib42.a:
	$(MAKE) -C libs

clean:
	$(MAKE) -C libs clean
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C libs fclean
	rm -rf $(BIN)

re: fclean all

.PHONY: all clean fclean

GREEN			:=	\033[1;32m
RESET			:= \033[0m
