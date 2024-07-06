# Directories
SRC_DIR      := ./src
OBJ_DIR      := ./obj
INCLUDES_DIR := ./includes
LIBFT_DIR    := ./libft
LIBFT        := $(LIBFT_DIR)/libft.a

# Compiler and flags
CC       := gcc
LEAKCHECK:= #-fsanitize=address
CFLAGS   := -g -O3 -Wall -Wextra -Werror -Wno-unused-result $(LEAKCHECK)
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
                env_manager_utils.c \
                env_manager.c \
				error_msg_utils.c \
                error_msg.c \
				free_shell.c \
				history_free.c \
                history.c \
                execute_commands.c \
				execute_commands_utils.c \
                redirect_heredoc.c \
				redirect_heredoc1.c \
				redirect_heredoc2.c \
                redirect_input.c \
				redirect_output.c \
                shell.c \
                signals_1.c \
				signals_2.c \
                sutils_1.c \
				sutils_2.c \
                builtins/builtin_cd.c \
                builtins/builtin_echo.c \
                builtins/builtin_env.c \
                builtins/builtin_export_utils_1.c \
                builtins/builtin_export_utils_2.c \
				builtins/builtin_export_utils_3.c \
                builtins/builtin_export.c \
                builtins/builtin_exit.c \
                builtins/builtin_pwd.c \
                builtins/builtin_unset.c \
				pipex/exec_cmd.c \
				pipex/execute_1.c \
				pipex/execute_2.c \
				pipex/execute_3.c \
				pipex/execute_4.c \
				pipex/execute_5.c \
				pipex/execute_utils_1.c \
				pipex/get_command_array_utils.c \
				pipex/get_command_array.c \
				pipex/get_command_path_utils.c \
				pipex/get_command_path.c \
				pipex/pipex_utils_1.c \
				pipex/pipex_utils_2.c \
				pipex/pipex_utils_3.c \
				pipex/pipex_utils_4.c \
                pipex/pipex.c \
                tokenizer/create_token.c \
                tokenizer/tokenizer_utils_1.c \
				tokenizer/tokenizer_utils_2.c \
				tokenizer/tokenizer_utils_3.c \
				tokenizer/tokenizer_utils_4.c \
				tokenizer/tokenizer_utils_5.c \
                tokenizer/tokenizer.c \
				parser/handle_expr.c \
                parser/join_tokens.c \
				parser/join_tokens_utils.c \
				parser/parse_double_quotes_utils_1.c \
				parser/parse_double_quotes_utils_2.c \
				parser/parse_double_quotes_utils_3.c \
				parser/parse_double_quotes_utils_4.c \
				parser/parse_double_quotes_utils_5.c \
				parser/parse_double_quotes.c \
				parser/parse_semicolon.c \
				parser/parse_single_quotes.c \
				parser/parser_utils.c \
				parser/parser_utils_2.c \
				parser/parse_value.c \
				parser/remove_embedded_quotes_utils.c \
				parser/remove_embedded_quotes.c \
                parser/parser.c \

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_FILES := $(SRC_FILES:.c=.o)
OBJ       := $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Compilation rules
$(NAME): $(LIBFT) $(OBJ) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS) $(IFLAGS)

all: $(NAME)
	@echo "\033[0;32m"
	@echo "_____________________________________"
	@echo "   __  ____      _     __       ____ "
	@echo "  /  |/  (_)__  (_)__ / /  ___ / / / "
	@echo " / /|_/ / / _ \/ (_-</ _ \/ -_) / /  "
	@echo "/_/  /_/_/_//_/_/___/_//_/\__/_/_/   "
	@echo "       Compilation Complete          "
	@echo "_____________________________________"
	@echo "\033[0m"
bonus: all

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(IFLAGS)

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

ASCII_ART := $(call ASCII_ART)

# Norminette
norm:
	@$(NORM) $(SRC_DIR)/*.c $(INCLUDES_DIR)/*.h

.PHONY: norm

# Custom commands
leaks: $(NAME)
	valgrind -s --leak-check=full --show-reachable=yes \
	--show-leak-kinds=all --trace-children=yes --track-fds=yes \
	--suppressions=./readline.supp \
	--track-origins=yes \
	./minishell

.PHONY: leaks
