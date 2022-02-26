# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/07 21:47:42 by fnichola          #+#    #+#              #
#    Updated: 2021/10/24 21:46:43 by fnichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

HEADER = libft.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS = ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c

OBJS = $(SRCS:.c=.o)

BONUS_SRCS = ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_printf.c \
	ft_print_num.c \
	ft_print_unum.c \
	ft_printf_fd.c \
	ft_print_num_fd.c \
	ft_print_unum_fd.c

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

ifdef WITH_BONUS
OBJS += $(BONUS_OBJS)
endif


all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	ar rcs $@ $^

bonus:
	$(MAKE) WITH_BONUS=1

clean:
	$(RM) $(OBJS)
	$(RM) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
