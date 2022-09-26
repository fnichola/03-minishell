# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 18:01:32 by fnichola          #+#    #+#              #
#    Updated: 2022/09/26 00:37:46 by fnichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wextra -Werror -Wall -g -fsanitize=address

SRCS = srcs/main.c \
	srcs/execute/execute-commands.c \
	srcs/execute/exec-fds.c \
	srcs/lexer/lexer.c \
	srcs/lexer/lex-functions.c \
	srcs/lexer/lex-utilities.c \
	srcs/lexer/lex-init.c \
	srcs/parser/parser.c \
	srcs/parser/parser-functions.c \
	srcs/parser/parser-init.c \
	srcs/parser/expand-quoted-text.c \
	srcs/built_in/built_in_command1.c \
	srcs/built_in/built_in_command2.c \
	srcs/utilities/argv_len.c \
	srcs/utilities/env_functions.c \
	srcs/utilities/exit_error.c \
	srcs/utilities/ft_perror.c \
	srcs/utilities/ft_puterror.c \
	srcs/utilities/ft_strcmp.c \
	srcs/utilities/is_str_match.c \
	srcs/utilities/malloc_error_check.c \
	srcs/utilities/str_tolower.c \
	srcs/utilities/wrapper.c

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
