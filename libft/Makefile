# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axlee <axlee@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 15:19:53 by axlee             #+#    #+#              #
#    Updated: 2024/06/23 16:07:35 by axlee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a

SRCS_DIR		= ./libft
OBJS_DIR		= ./obj
INCLUDES_DIR	= ./includes

PRINTF_DIR		= ./ft_printf
PRINTF 			= $(PRINTF_DIR)/libftprintf.a

GNL_DIR			=./gnl

VPATH			= libft:libft/file: \
					libft/list: \
					libft/mem: \
					libft/nbr: \
					libft/others: \
					libft/str: \
					gnl \


CC				= gcc
CFLAGS			= -Wall -Wextra -Werror #$(LEAKCHECK)
LEAKCHECK		= -g -fsanitize=address
LFLAGS 			= -L. -I$(INCLUDES_DIR)

RM				= rm -f
NORM			= norminette

INCLUDES_FILES	= libft.h
INCLUDES		= $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

# **************************************************************************** #
#                               FILE FUNCTIONS                                 #
# **************************************************************************** #

FILE_FILES =	file/ft_lstnew.c \
				file/ft_lstsize.c \
				file/ft_putchar_fd.c \
				file/ft_putendl_fd.c \
				file/ft_putnbr_fd.c \
				file/ft_putstr_fd.c \

FILE_OBJS =		$(addprefix $(OBJS_DIR)/,$(notdir $(FILE_FILES:.c=.o)))

# **************************************************************************** #
#                               LIST FUNCTIONS                                 #
# **************************************************************************** #

LIST_FILES =	list/ft_lstadd_back.c \
				list/ft_lstadd_front.c \
				list/ft_lstclear.c \
				list/ft_lstdelone.c \
				list/ft_lstlast.c \
				list/ft_lstmap.c \

LIST_OBJS =		$(addprefix $(OBJS_DIR)/,$(notdir $(LIST_FILES:.c=.o)))


# **************************************************************************** #
#                             MEMORY FUNCTIONS                                 #
# **************************************************************************** #

MEM_FILES =		mem/ft_bzero.c \
				mem/ft_calloc.c \
				mem/ft_memccpy.c \
				mem/ft_memchr.c \
				mem/ft_memcmp.c \
				mem/ft_memcpy.c \
				mem/ft_memmove.c \
				mem/ft_memset.c \

MEM_OBJS =		$(addprefix $(OBJS_DIR)/,$(notdir $(MEM_FILES:.c=.o)))

# **************************************************************************** #
#                              NBR FUNCTIONS                                   #
# **************************************************************************** #

NBR_FILES =		nbr/ft_atof.c \
				nbr/ft_atoi.c \
				nbr/ft_dtoa.c \
				nbr/ft_itoa.c \
				nbr/ft_ltoa.c \
				nbr/ft_nbr_base.c \

NBR_OBJS =		$(addprefix $(OBJS_DIR)/,$(notdir $(NBR_FILES:.c=.o)))

# **************************************************************************** #
#                           OTHERS FUNCTIONS                                   #
# **************************************************************************** #

OTHERS_FILES =	others/add_char.c \
				others/ft_isalnum.c \
				others/ft_isalpha.c \
				others/ft_isascii.c \
				others/ft_isdigit.c \
				others/ft_isnumeric.c \
				others/ft_isprint.c \
				others/ft_isspace.c

OTHERS_OBJS =		$(addprefix $(OBJS_DIR)/,$(notdir $(OTHERS_FILES:.c=.o)))

# **************************************************************************** #
#                              STR FUNCTIONS                                   #
# **************************************************************************** #

STR_FILES =		str/ft_split_free.c \
				str/ft_split.c \
				str/ft_sprintf.c \
				str/ft_strcat.c \
				str/ft_strccmp.c \
				str/ft_strchr.c \
				str/ft_strcmp.c \
				str/ft_strcpy.c \
				str/ft_strdel.c \
				str/ft_strdup.c \
				str/ft_striteri.c \
				str/ft_strjoin.c \
				str/ft_strlcat.c \
				str/ft_strlcpy.c \
				str/ft_strlen.c \
				str/ft_strmapi.c \
				str/ft_strncat.c \
				str/ft_strncmp.c \
				str/ft_strncpy.c \
				str/ft_strndup.c \
				str/ft_strnstr.c \
				str/ft_strrchr.c \
				str/ft_strswap.c \
				str/ft_strtrim.c \
				str/ft_substr.c \
				str/ft_tolower.c \
				str/ft_toupper.c

STR_OBJS =		$(addprefix $(OBJS_DIR)/,$(notdir $(STR_FILES:.c=.o)))

# **************************************************************************** #
#                              GET NEXT LINE                                   #
# **************************************************************************** #

GNL_FILES =		gnl/get_next_line.c

GNL_OBJS =		$(addprefix $(OBJS_DIR)/,$(notdir $(GNL_FILES:.c=.o)))

# **************************************************************************** #
#                                   MAKE                                       #
# **************************************************************************** #

$(NAME):		$(OBJS_DIR) $(FILE_OBJS) $(GNL_OBJS) $(LIST_OBJS) $(MEM_OBJS) \
				$(NBR_OBJS) $(OTHERS_OBJS) $(STR_OBJS)
				@ar rcs $(NAME) $(FILE_OBJS) $(GNL_OBJS) $(LIST_OBJS) \
				$(MEM_OBJS) $(NBR_OBJS) $(OTHERS_OBJS) $(STR_OBJS)


all:			$(NAME)

bonus:			all

printf:			$(NAME)
				@make -C $(PRINTF_DIR) --no-print-directory
				@cp $(PRINTF) $(NAME)

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@


.PHONY:			all bonus printf

# **************************************************************************** #
#                                   CLEAN                                      #
# **************************************************************************** #

clean:
				@make -C $(PRINTF_DIR) clean --no-print-directory
				@$(RM) $(FILE_OBJS)
				@$(RM) $(GNL_OBJS)
				@$(RM) $(LIST_OBJS)
				@$(RM) $(MEM_OBJS)
				@$(RM) $(NBR_OBJS)
				@$(RM) $(OTHERS_OBJS)
				@$(RM) $(STR_OBJS)

fclean:			clean
				@make -C $(PRINTF_DIR) fclean --no-print-directory
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
