LIBFT_PATH	= ./libft
LIBFT		= $(LIBFT_PATH)/libft.a

SRC_DIR			= src

# Compiler and Flags
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -Iincludes -I/usr/include/readline

LIBS			= -L$(LIBFT_PATH) -lft -lreadline

SRC_FILES		= $(addprefix $(SRC_DIR)/, \
					main.c \
					sutils.c \
					history.c \
					pipex.c \
					pipex_utils.c \
					signals.c \
					tokenizer/tokenizer.c \
					tokenizer/tokenizer_utils.c)

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
