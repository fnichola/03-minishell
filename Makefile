# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 18:01:32 by fnichola          #+#    #+#              #
#    Updated: 2022/04/19 21:25:43 by fnichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

SRCS = srcs/main.c \
	srcs/lexer/lexer.c \
	srcs/lexer/lex-functions.c \
	srcs/lexer/lex-utilities.c \
	srcs/lexer/lex-init.c \
	srcs/parser/parser.c \
	srcs/parser/parse-functions.c \
	srcs/parser/parse-init.c \
	srcs/utilities.c

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
