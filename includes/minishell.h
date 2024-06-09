/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:39:49 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/09 13:46:42 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "\033[1;32mminishell$ \033[0m"
# define BASE_ENV_SIZE 64
# define TRUE 0
# define FALSE 1

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
}					t_token_type;

// token structure
typedef struct s_token
{
	char			*token;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
	int				is_single_quoted;
}					t_token;

// Struct for commands
typedef struct s_cmd
{
	t_token_type	type;
	int				argc;
	char			**argv;
	t_list			*input;
	t_list			*output;
	int				return_value;
}					t_cmd;

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
	int		signal_received;
	bool	end;
}	t_shell;


// Error Message
void				delete_command(void *elem);
void				free_and_exit(t_shell *minishell, int return_value);
int					minishell_error_msg(char *cmd, int error_no);

// builtins
void				minishell_echo(t_shell *minishell);
void				minishell_exit(t_shell *minishell);
void				print_vars(t_shell *minishell);
void				env_realloc(t_shell *minishell);
void				minishell_pwd(void);
int					count_tokens(t_shell *minishell);
int					minishell_cd(t_shell *minishell);
int					minishell_export(t_shell *minishell);
int					minishell_unset(t_shell *minishell);
int					search_env(t_shell *minishell, char *var);
int					minishell_env(t_shell *minishell);
char				*join_from_index(char **cmd, int start_index);

// utils
int					ft_strcmp(const char *s1, const char *s2);
char				**ft_dqsplit(char const *s, char c);
void				convert_cmd(char **s);

// ENV_Manager
char				*get_env_value(t_shell *minishell, const char *var);
int					env_len(t_shell *minishell);
int					search_env_by_var(t_shell *minishell, const char *var);
void				sort_env(t_shell *minishell);
void				init_env(t_shell *minishell, char **envp);
void				set_env(t_shell *minishell, const char *var,
						const char *value);
void				set_env_entry(t_shell *minishell, char *new_entry, int idx);

// redirect
int					execute_parent(int pid, int *pipe_des);
int					here_doc(t_shell *minishell, char *delimiter);
int					redirect_input(t_shell *minishell, t_token *curr);
int					redirect_output(t_shell *minishell, t_token *curr);

// redirect utils
char				*join_and_free(char *s1, const char *s2);
char				*expand_env_variable(char *str, t_shell *minishell);
int					read_input(char **str, char *delimiter);
int					is_delimiter(const char *str, const char *delimiter);
void				signal_exit(int signal_number);
void				error_eof(char *end_of_file);

// signals
void				sigquit_handler(int signal);
void				sigint_handler(int signal);
void				setup_signal_handler(void);
void				sigint_handler1(int signal);

// history
int					print_history(void);
int					hist_feature(const char *s);
void				prompt(void);

void				delete_command(void *elem);
void				free_and_exit(t_shell *minishell, int return_value);
char				*ft_strjoin_free(char **s1, char const *s2);
int					minishell_error_msg(char *cmd, int error_no);

// pipex(execute)
void				execute_single_command(t_token *curr, t_shell *minishell);
void				execute_pipeline(t_token *curr, t_shell *minishell);
void				execute_with_redirection(t_token *token, t_shell *minishell,
						int index);
void				execute_builtin_or_exec_exit(t_token *curr,
						t_shell *minishell);
void				execute_builtin_or_exec(t_token *curr, t_shell *minishell);

// pipex(execute_utils)
int					check_command(char *cmd, t_shell *minishell);
char				**get_command_array(char *cmd, t_shell *minishell);
void				load_previous_fd(t_shell *minishell);
char				*get_command_path(char **s_cmd, t_shell *minishell);
void				exec_cmd(t_token *curr, t_shell *minishell);

// pipex(utils)
void				exit_handler(int exit_code);
void				ft_free_tab(char **tab);
void				restore_fds(int input_fd, int output_fd);
int					open_file(const char *file, int mode);
char				*get_path(char *cmd, t_shell *minishell);

// pipex(utils1)
int					num_of_commands(t_shell *minishell);
int					num_of_pipes(t_shell *minishell);
int					num_of_arguments(t_shell *minishell);
t_token				*move_lst_by_index(t_token *curr, int index);

// pipex(utils2)
int					check_redirection_type(t_token *curr);
int					check_for_redirections(t_shell *minishell);

// pipex
int					handle_redirection(t_shell *minishell, t_token *curr);
t_token				*handle_builtins(t_token *curr, t_shell *minishell);
void				pipex(t_shell *minishell);

// tokenizer
void				token_add_back(t_token **head, char *token,
						t_token_type type);
void				handle_environment_variable(char **line,
						t_token **token_lst, t_shell *minishell);
void				handle_remaining_text(char **line, t_token **token_lst);
void				handle_backslash(char **line, t_token **token_lst);
void				handle_quotes(char **line, t_token **token_lst);
void				free_tokenlst(t_token *head);
void				print_tokenlst(t_token *token_lst);
int					ft_iswhitespace(char *line);
int					ft_isbackslash(char *line);
int					add_symbol_lst(char **line, t_token_type type,
						t_token **token_lst);
int					add_command_lst(char **line, t_token **token_lst);
char				*ft_copy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
size_t				ft_wordlen(const char *s, char c);
t_token				*create_token(char *token, t_token_type type);
t_token				*token_processor(char *line, t_shell *minishell);

// parser(join_tokens)
void				join_identifier_tokens(t_token *lst);

// parser(parse_single_quotes)
void				parse_single_quotes(t_token *token);

// parser(parse_double_quotes)
void				parse_double_quotes(t_token *token);

// parser(parse_double_quotes_utils_1)
void				handle_special_env_variable(char *result, int *i, int *j,
						t_shell *minishell);
void				extract_variable_name(char *str, int *i, char **var_name,
						int *var_len);
void				handle_regular_env_variable(char *str, char *result, int *i,
						t_shell *minishell);
void				handle_env_variable_expansion(char *str, char *result,
						int *i, t_shell *minishell);

// parser(parse_double_quotes_utils_2)
void	initialize_parse_variables(t_token *token, char **str, int *len, char **result);

void				process_dollar_character(char *str, char *result, int *i,
						int *j);
void				process_character(char *str, char *result, int *i, int *j);

// parser(parse_semicolon)
void				parse_semicolon(t_token *token);

// parser(parse_value)
void				handle_env_variable(t_token *curr, t_shell *minishell);
void				handle_exit_status(t_token *curr, t_shell *minishell);
void				handle_exit_status_with_suffix(t_token *curr,
						t_shell *minishell, const char *suffix);
void				parse_value(t_token *token_lst, t_shell *minishell);

// parser
void				set_token_pointers(t_token *tokens);
void				parse_token(t_token *token, t_shell *minishell);
t_token				*token_parser(t_token *token_lst, t_shell *minishell);

// parser(remove_embedded_quotes)
void				remove_embedded_quotes(t_token *token);
int					find_first_quote(char *str, int len);
int					find_last_quote(char *str, int len, int first_quote_index,
						char quote_char);

int					check_quotes_in_between(char *str, int first_quote_index,
						int last_quote_index, char quote_char);
char				*remove_quotes(char *str, int first_quote_index,
						int last_quote_index, int len);

// parser(remove_embedded_quotes_utils)
void				update_token_if_needed(t_token *token, char *new_str);
void				free_and_replace_token(t_token *token, char *new_str);

// execute_commands.c
int					check_builtin(char *s);
int					execute_builtin_1(t_token *curr, t_shell *minishell);
int					execute_builtin_2(t_token *curr, t_shell *minishell);
int					other_cmds(t_token *curr, t_shell *minishell);

// shell.c
t_shell				*init_shell(void);
void				free_shell(t_shell *minishell);
void				initialize_shell(t_shell **minishell, char **envp);
void				cleanup(t_shell *g_shell);
void				reset_process_ids(t_shell *minishell);

// main.c
char				*read_input_line(t_shell *g_shell);
void				process_command_line(t_shell *minishell, char *line);
void				main_loop(t_shell *g_shell);

#endif
