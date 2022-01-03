# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaehpark <jaehpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 02:30:08 by jaehpark          #+#    #+#              #
#    Updated: 2022/01/03 09:34:39 by jaehpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

CC				= gcc
CFLAGS			= -g -g3 -fsanitize=address -Wall -Werror -Wextra

LDFLAGS			="-L/Users/$(USER)/.brew/opt/readline/lib"
CPPFLAGS		="-I/Users/$(USER)/.brew/opt/readline/include"

INCS			= -Ilibft -I.

SRCS_DIR		= srcs
SRCS_NAME		= main.c \
					setting.c \
					utils.c \
					parse.c \
					parse_utils.c \
					split_token.c \
					expand.c

SRCS			= $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))

OBJS_DIR		= objs
OBJS			= $(addprefix $(OBJS_DIR)/, $(SRCS_NAME:.c=.o))

LIB_DIR			= libft
LIB_NAME		= ft
LIB				= $(addprefix $(LIB_DIR)/, libft.a)

$(NAME)			: $(LIB) $(OBJS)
					$(CC) $(CFLAGS) $(INCS) -L$(LIB_DIR) -l$(LIB_NAME) -lreadline $(LDFLAGS) $(CPPFLAGS) -lncurses $(OBJS) -o $@

$(LIB)			:
					$(MAKE) -C $(LIB_DIR) all
					$(MAKE) -C $(LIB_DIR) bonus

$(OBJS_DIR)/%.o	: $(SRCS_DIR)/%.c
					mkdir -p $(OBJS_DIR)
					$(CC) $(CFLAGS) $(INCS) -c $< -o $@

all				: $(NAME)

clean			:
					$(MAKE) -C $(LIB_DIR) clean
					rm -rf $(OBJS_DIR)

fclean			:
					$(MAKE) -C $(LIB_DIR) fclean
					rm -rf $(NAME) $(OBJS_DIR)

re				: fclean all

.PHONY			: all clean fclean re bonus
