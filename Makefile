# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnichola <fnichola@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/09 18:01:32 by fnichola          #+#    #+#              #
#    Updated: 2022/10/30 18:09:06 by fnichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
READLINE_DIR = $(shell brew --prefix readline)
# READLINE_DIR = /usr/local/Cellar/readline/8.1.2/lib/
CC = gcc
CFLAGS = -Wextra -Werror -Wall -g -fsanitize=address -I $(READLINE_DIR)/include
LDFLAGS = -lreadline -lhistory -L$(READLINE_DIR)/lib
SRCS = srcs/main.c \
	srcs/execute/execute-commands.c \
	srcs/execute/execute-built-in.c \
	srcs/execute/execute-external.c \
	srcs/execute/exec-fds.c \
	srcs/execute/exec-fds2.c \
	srcs/lexer/lexer.c \
	srcs/lexer/lex-functions.c \
	srcs/lexer/lex-functions2.c \
	srcs/lexer/lex-utilities.c \
	srcs/lexer/lex-utilities2.c \
	srcs/lexer/lex-init.c \
	srcs/parser/parser.c \
	srcs/parser/parser-functions.c \
	srcs/parser/parser-functions2.c \
	srcs/parser/parser-init.c \
	srcs/parser/expand-quoted-text.c \
	srcs/built-in/built-in-cd.c \
	srcs/built-in/built-in-echo.c \
	srcs/built-in/built-in-env.c \
	srcs/built-in/built-in-exit.c \
	srcs/built-in/built-in-pwd.c \
	srcs/built-in/built-in-unset.c \
	srcs/built-in/export.c \
	srcs/built-in/export2.c \
	srcs/built-in/init-built-in-table.c \
	srcs/utilities/del_token.c \
	srcs/utilities/exit_error.c \
	srcs/utilities/ft_atoi_err.c \
	srcs/utilities/ft_perror.c \
	srcs/utilities/ft_puterror.c \
	srcs/utilities/ft_strncpy.c \
	srcs/utilities/ft_strcmp.c \
	srcs/utilities/heredoc.c \
	srcs/utilities/heredoc-utils.c \
	srcs/utilities/is_str_match.c \
	srcs/utilities/is_valid_var_char.c \
	srcs/utilities/malloc_error_check.c \
	srcs/utilities/str_tolower.c \
	srcs/utilities/wrapper.c \
	srcs/utilities/command/command_add_back.c \
	srcs/utilities/command/del_command.c \
	srcs/utilities/command/free_command_table.c \
	srcs/utilities/command/free_command.c \
	srcs/utilities/env/env_list_add_back.c \
	srcs/utilities/env/env_list_copy_all.c \
	srcs/utilities/env/env_list_dup.c \
	srcs/utilities/env/env_list_first.c \
	srcs/utilities/env/env_list_last.c \
	srcs/utilities/env/env_list_new.c \
	srcs/utilities/env/env_list_size.c \
	srcs/utilities/env/env_list_sort.c \
	srcs/utilities/env/env_list_swap_next.c \
	srcs/utilities/env/env_to_string.c \
	srcs/utilities/env/export_to_envp.c \
	srcs/utilities/env/free_env_list.c \
	srcs/utilities/env/free_envp.c \
	srcs/utilities/env/ft_findenv.c \
	srcs/utilities/env/ft_getenv.c \
	srcs/utilities/env/ft_setenv.c \
	srcs/utilities/env/ft_unset_env.c \
	srcs/utilities/env/get_env_name.c \
	srcs/utilities/env/get_env_value.c \
	srcs/utilities/env/init_env_list.c \
	srcs/utilities/env/split_env.c \
	srcs/utilities/gnl/get_next_line.c \
	srcs/utilities/gnl/get_next_line_utils.c \
	srcs/utilities/redirect/free_redirects.c \
	srcs/utilities/redirect/redirect_add.c \
	srcs/utilities/redirect/redirect_new.c \
	srcs/signals/signal.c \
	srcs/exit/exit_status.c \
	srcs/utilities/inits.c \

ifdef WITH_BONUS
endif

# $(warning $(READLINE_DIR))

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -I includes -o $@ -c $<
	
$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBFT_LIB) -lncurses -I ./includes -o $(NAME)

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
