# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akihito <akihito@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 18:01:32 by fnichola          #+#    #+#              #
#    Updated: 2022/08/28 18:02:37 by akihito          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -g -fsanitize=address

SRCS = srcs/main.c \
	srcs/lexer/lexer.c \
	srcs/lexer/lex-functions.c \
	srcs/lexer/lex-utilities.c \
	srcs/lexer/lex-init.c \
	srcs/parser/parser.c \
	srcs/parser/parser-functions.c \
	srcs/parser/parser-functions2.c \
	srcs/parser/parser-functions3.c \
	srcs/parser/parser-init.c \
	srcs/parser/expand-quoted-text.c \
	srcs/parser/fd_utils.c \
	srcs/utilities.c \
	srcs/built_in/built_in_command1.c \
	srcs/built_in/built_in_utils.c \
	srcs/utils/env_functions.c \
	srcs/utils/wrapper.c \

ifdef WITH_BONUS
endif

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -I includes -o $@ -c $<
	
$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -lreadline -lncurses -I includes -o $(NAME)

$(LIBFT_LIB):
	$(MAKE) bonus -C $(LIBFT_DIR)

bonus:
	$(MAKE) WITH_BONUS=1

clean:
	$(RM) $(OBJS) $(DEPS)
	$(MAKE) clean WITH_BONUS=1 -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_LIB)

re: fclean all

.PHONY: all clean fclean re bonus

-include $(DEPS)
