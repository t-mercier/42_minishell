# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: asaijers <asaijers@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/03/02 13:48:01 by asaijers      #+#    #+#                  #
#    Updated: 2023/03/02 13:48:01 by asaijers      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


CC = cc
AR = ar
CFLAGS += -Wall -Wextra -Werror -g
NAME = lib42.a
OUT = out/
SRCS = ft_alloc.c ft_is1.c ft_is2.c ft_list1.c ft_list2.c \
	ft_mem.c ft_misc.c ft_printf1.c ft_printf2.c ft_printf3.c ft_printf4.c \
	ft_put.c ft_str1.c ft_str2.c ft_str3.c ft_str4.c ft_to.c \
	gnl.c gnl_util.c \
	v1.c v2.c v3.c v4.c

OBJS = $(addprefix $(OUT),$(SRCS:.c=.o))

all: $(NAME)

$(OUT)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar crs $(NAME) $(OBJS)

bonus: $(NAME)

clean:
	rm -rf $(OUT)

fclean: clean
	rm -rf '$(NAME)'

re: fclean all
