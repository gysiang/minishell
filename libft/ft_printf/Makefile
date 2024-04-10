# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axlee <axlee@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 17:21:31 by axlee             #+#    #+#              #
#    Updated: 2024/03/13 17:21:34 by axlee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= libftprintf.a

SRCS_DIR		= ./src
OBJS_DIR		= ./obj
INCLUDES_DIR	= ../includes

LIBFT_DIR		= ../
LIBFT			= $(LIBFT_DIR)/libft.a

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror #$(LEAKCHECK)
LEAKCHECK		= -g -fsanitize=address
LFLAGS 			= -L$(LIBFT_DIR) -I$(INCLUDES_DIR)

RM				= rm -f
NORM			= norminette

INCLUDES_FILES	= ft_printf.h
INCLUDES		= $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

# **************************************************************************** #
#                                 FT_PRINTF                                    #
# **************************************************************************** #

SRCS =			ft_printf.c \
				flag_parse.c \
				format_str_string.c \
				format_nbr_string.c \
				format_hex_string.c

OBJS =			$(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

# **************************************************************************** #
#                                   MAKE                                       #
# **************************************************************************** #

$(NAME):		$(LIBFT) $(OBJS_DIR) $(OBJS)
				@cp $(LIBFT) $(NAME)
				@ar rcs $(NAME) $(OBJS)

all:			$(NAME)

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)

${OBJS_DIR}/%.o: $(SRCS_DIR)/%.c $(INCLUDES)
				@$(CC) -c $< -o $@ $(LFLAGS)

bonus:			$(NAME)

.PHONY:			all bonus

# **************************************************************************** #
#                                   CLEAN                                      #
# **************************************************************************** #

clean:
				@$(RM) $(OBJS)

fclean:			clean
				@$(RM) $(NAME)
				@rm -rf $(OBJS_DIR)

re:				fclean all

.PHONY:			clean fclean re

# **************************************************************************** #
#                                NORMINETTE                                    #
# **************************************************************************** #

norm:
				@$(NORM) $(SRCS_DIR)/*.c $(INCLUDES_DIR)/*.h

.PHONY:			norm