/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:39:49 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/06 10:34:09 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <limits.h>

# define PROMPT "\033[1;32mminishell$ \033[0m"
# define BASE_ENV_SIZE 64
# define TRUE			0
# define FALSE			1

// token types
typedef enum s_token_type
{
	T_IDENTIFIER,
	T_PIPE,
	T_LESSER_THAN,
	T_GREATER_THAN,
	T_LEFT_SHIFT,
	T_RIGHT_SHIFT,
	T_SINGLEQUOTE,
	T_DOUBLEQUOTE,
	T_ENV_ASSIGNMENT,
}	t_token_type;

// token structure
typedef struct s_token
{
	char			*token;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
	int	is_single_quoted;
}	t_token;

// Struct for commands
typedef struct s_cmd
{
	t_token_type	type;
	int				argc;
	char			**argv;
	t_list			*input;
	t_list			*output;
	int				return_value;
}	t_cmd;

/*
 * Struct for Minishell
*/

typedef struct s_shell
{
	int		env_size;
	int		exit;
	char	**env;
	char	*prompt;
	t_token	*cmd_list;
	int		input_fd;
	int		output_fd;
	int		prev_fd;
	pid_t	process_ids[100];
	int		process_count;
	int		last_return;
	bool	end;
}	t_shell;

extern int	g_signal_received;

// Error Message
void	delete_command(void *elem);
void	free_and_exit(t_shell *minishell, int return_value);
int		minishell_error_msg(char *cmd, int error_no);

// builtins
void	minishell_echo(t_shell *minishell);
void	minishell_exit(t_shell *minishell);
void	print_vars(t_shell *minishell);
void	env_realloc(t_shell *minishell);
void	minishell_pwd(void);
int		count_tokens(t_shell *minishell);
int		minishell_cd(t_shell *minishell);
int		minishell_export(t_shell *minishell);
int		minishell_unset(t_shell *minishell);
int		search_env(t_shell *minishell, char *var);
int		minishell_env(t_shell *minishell);
char	*join_from_index(char **cmd, int start_index);

// utils
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_dqsplit(char const *s, char c);
void	convert_cmd(char **s);

// ENV_Manager
char	*get_env_value(t_shell *minishell, const char *var);
int		env_len(t_shell *minishell);
int		search_env_by_var(t_shell *minishell, const char *var);
void	sort_env(t_shell *minishell);
void	init_env(t_shell *minishell, char **envp);
void	set_env(t_shell *minishell, const char *var, const char *value);
void	set_env_entry(t_shell *minishell, char *new_entry, int idx);

// redirect
int		here_doc(t_shell *minishell, char *delimiter);
int		redirect_input(t_shell *minishell, t_token *curr);
int		redirect_output(t_shell *minishell, t_token *curr);

// signals
void	sigquit_handler(int signal);
void	sigint_handler(int signal);
void	setup_signal_handler(void);
void	sigint_handler1(int signal);

//history
int		print_history(void);
int		hist_feature(const char *s);
void	prompt(void);

void	delete_command(void *elem);
void	free_and_exit(t_shell *minishell, int return_value);
char	*ft_strjoin_free(char **s1, char const *s2);
int		minishell_error_msg(char *cmd, int error_no);

//pipex(execute)
void	execute_single_command(t_token *curr, t_shell *minishell);
void	execute_pipeline(t_token *curr, t_shell *minishell);
void	execute_with_redirection(t_token *token, t_shell *minishell, int index);
void	execute_builtin_or_exec_exit(t_token *curr, t_shell *minishell);
void	execute_builtin_or_exec(t_token *curr, t_shell *minishell);


//pipex(execute_utils)
int	check_command(char *cmd, t_shell *minishell);
char	**get_command_array(char *cmd, t_shell *minishell);
void	load_previous_fd(t_shell *minishell);
char	*get_command_path(char **s_cmd, t_shell *minishell);
void	exec_cmd(t_token *curr, t_shell *minishell);

//pipex(utils)
void	exit_handler(int exit_code);
void	ft_free_tab(char **tab);
void	restore_fds(int input_fd, int output_fd);
int		open_file(const char *file, int mode);
char	*get_path(char *cmd, t_shell *minishell);

//pipex(utils1)
int		num_of_commands(t_shell *minishell);
int		num_of_pipes(t_shell *minishell);
int		num_of_arguments(t_shell *minishell);
t_token	*move_lst_by_index(t_token *curr, int index);

//pipex(utils2)
int		check_redirection_type(t_token *curr);
int		check_for_redirections(t_shell *minishell);

//pipex
int		handle_redirection(t_shell *minishell, t_token *curr);
t_token	*handle_builtins(t_token *curr, t_shell *minishell);
void	pipex(t_shell *minishell);

// tokenizer
void	token_add_back(t_token **head, char *token, t_token_type type);
void	handle_environment_variable(char **line, t_token **token_lst,
			t_shell *minishell);
void	handle_remaining_text(char **line, t_token **token_lst);
void	handle_backslash(char **line, t_token **token_lst);
void	handle_quotes(char **line, t_token **token_lst);
void	free_tokenlst(t_token *head);
void	print_tokenlst(t_token *token_lst);
int		ft_iswhitespace(char *line);
int		ft_isbackslash(char *line);
int		add_symbol_lst(char **line, t_token_type type, t_token **token_lst);
int		add_command_lst(char **line, t_token **token_lst);
char	*ft_copy(char *dest, const char *src, size_t n);
char	*ft_strcat(char *dest, const char *src);
size_t	ft_wordlen(const char *s, char c);
t_token	*create_token(char *token, t_token_type type);
t_token	*token_processor(char *line, t_shell *minishell);

// parser
void	parse_semicolon(t_token *token);
void	handle_env_variable(t_token *curr, t_shell *minishell);
void	parse_value(t_token *token_lst, t_shell *minishell);
void	set_token_pointers(t_token *tokens);
void	handle_exit_status(t_token *curr, t_shell *minishell);
void	handle_exit_status_with_suffix(t_token *curr, t_shell *minishell, const char *suffix);
void 	parse_single_quotes(t_token *token);
void 	parse_double_quotes(t_token *token, t_shell *minishell);
void	parse_token(t_token *token, t_shell *minishell);
void	join_identifier_tokens(t_token *lst);
t_token	*token_parser(t_token *token_lst, t_shell *minishell);

//execute_commands.c
int		check_builtin(char *s);
int		execute_builtin_1(t_token *curr, t_shell *minishell);
int		execute_builtin_2(t_token *curr, t_shell *minishell);
int		other_cmds(t_token *curr, t_shell *minishell);

//shell.c
t_shell	*init_shell(void);
void	free_shell(t_shell *minishell);
void	initialize_shell(t_shell **minishell, char **envp);
void	cleanup(t_shell *g_shell);
void	reset_process_ids(t_shell *minishell);

//main.c
char	*read_input_line(t_shell *g_shell);
void	process_command_line(t_shell *minishell, char *line);
void	main_loop(t_shell *g_shell);

#endif
