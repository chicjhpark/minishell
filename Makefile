# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 02:30:08 by jaehpark          #+#    #+#              #
#    Updated: 2022/01/09 06:42:42 by jaehpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= gcc
CFLAGS			= -g3 -fsanitize=address -Wall -Werror -Wextra

LIBR				:=
# LIBR				+= -I/opt/homebrew/Cellar/readline/8.1.1/include
# LIBR				+= -L/opt/homebrew/Cellar/readline/8.1.1/share/readline
LIBR				+= "-L/Users/$(USER)/.brew/opt/readline/lib"
LIBR				+= "-I/Users/$(USER)/.brew/opt/readline/include"
# LIBR         += -I/usr/local/opt/readline/include
# LIBR         += -L/usr/local/opt/readline/lib


LINKER			:=
LINKER			+= -Llibft -lft
LINKER			+= -lreadline

INCLUDES    	:=
# INCLUDES		+= -L/opt/homebrew/Cellar/readline/8.1.1/share/readline
INCLUDES		+= -I/opt/homebrew/Cellar/readline/8.1.1/include
# INCLUDES		+= -L/Users/jhpark/.brew/Cellar/readline/8.1.1/include
# INCLUDES		+= -L/Users/jhpark/.brew/Cellar/readline/8.1.1/include
# INCLUDES		+= -I/Users/jhpark/.brew/Cellar/readline/8.1.1/include
# INCLUDES		+= "-L/Users/$(USER)/.brew/opt/readline/lib"
# INCLUDES		+= "-I/Users/$(USER)/.brew/opt/readline/include"
# INCLUDES		+= -I/usr/local/opt/readline/include
# INCLUDES		+= -L/usr/local/opt/readline/lib
INCLUDES    	+= -I. -Ilibft
INCLUDES    	+= -I/usr/local/opt/readline/include

SRCS_DIR		= srcs
SRCS_NAME		= main.c \
					setting.c \
					utils.c \
					parse.c \
					parse_utils.c \
					split_token.c \
					expand.c \
					command.c \
					heredoc.c \
					builtin1.c \
					builtin2.c \
					builtin_exit.c \
					builtin_export.c \
					builtin_tools.c \
					expand_utils.c

SRCS			= $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))

OBJS_DIR		= objs
OBJS			= $(addprefix $(OBJS_DIR)/, $(SRCS_NAME:.c=.o))

LIB_DIR			= libft
LIB_NAME		= ft
LIB				= $(addprefix $(LIB_DIR)/, libft.a)

$(NAME)			: $(LIB) $(OBJS)
					$(CC) $(CFLAGS) $(INCLUDES) $(LIBR) $(LINKER) -lncurses $(OBJS) -o $@

$(LIB)			:
					$(MAKE) -C $(LIB_DIR) all
					$(MAKE) -C $(LIB_DIR) bonus

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.c
					mkdir -p $(OBJS_DIR)
					$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all				: $(NAME)

clean			:
					$(MAKE) -C $(LIB_DIR) clean
					rm -rf $(OBJS_DIR)

fclean			:
					$(MAKE) -C $(LIB_DIR) fclean
					rm -rf $(NAME) $(OBJS_DIR)

re				: fclean all

.PHONY			: all clean fclean re bonus
