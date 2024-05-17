# Directories
SRC_DIR      := ./src
OBJ_DIR      := ./obj
INCLUDES_DIR := ./includes
LIBFT_DIR    := ./libft
LIBFT        := $(LIBFT_DIR)/libft.a

# Compiler and flags
CC       := gcc
CFLAGS   := -O3 -Wall -Wextra -Werror -Wno-unused-result $(LEAKCHECK)
LEAKCHECK := -g -fsanitize=address
LFLAGS   := -L./libft -lft -lreadline
IFLAGS   := -I$(LIBFT_DIR) -I$(INCLUDES_DIR)

RM    := rm -f
NORM  := norminette

# Name of the executable
NAME := minishell

# Includes files
INCLUDES_FILES := minishell.h
INCLUDES       := $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

# Srcs
SRC_FILES := main.c \
             env_manager.c \
             error_msg.c \
             history.c \
             redirect_heredoc.c \
             redirect.c \
             signals.c \
             sutils.c \
             builtins/builtin_cd.c \
             builtins/builtin_echo.c \
             builtins/builtin_env.c \
             builtins/builtin_export_utils.c \
             builtins/builtin_export.c \
             builtins/builtin_exit.c \
             builtins/builtin_pwd.c \
             builtins/builtin_unset.c \
             pipex/pipex_utils.c \
             pipex/pipex.c \
			 tokenizer/create_token.c \
             tokenizer/tokenizer_utils.c \
             tokenizer/tokenizer.c \
			 parser/join_tokens.c \
			 parser/parser.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_FILES := $(SRC_FILES:.c=.o)
OBJ       := $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Compilation rules
$(NAME): $(LIBFT) $(OBJ) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS) $(IFLAGS)

all: $(NAME)

bonus: all

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)

.PHONY: all bonus

# Cleanup rules
clean:
	@make -C $(LIBFT_DIR) clean --no-print-directory
	$(RM) -r $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re

# Norminette
norm:
	@$(NORM) $(SRC_DIR)/*.c $(INCLUDES_DIR)/*.h

.PHONY: norm

# Custom commands
leaks: $(NAME)
	valgrind -s --leak-check=full --show-reachable=yes \
	--show-leak-kinds=all --trace-children=yes --track-fds=yes \
	--suppressions=suppression/readline.supp \
	./minishell

.PHONY: leaks
