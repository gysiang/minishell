LIBFT_PATH	= ./libft
LIBFT		= $(LIBFT_PATH)/libft.a

# Compiler and Flags
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

INCLUDES_DIR	= includes
SRC_DIR			= srcs

LIBS			= -L$(LIBFT_PATH) -lft

SRC_FILES		= $(addprefix $(SRC_DIR)/, \
					main.c)

NAME			= minishell

$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFT_PATH)

OBJECTS			= $(SRC_FILES:.c=.o)

#Targets

all: 		$(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(NAME)

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJECTS)


fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
