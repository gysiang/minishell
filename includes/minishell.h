/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:39:49 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/22 15:43:50 by gyong-si         ###   ########.fr       */
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
	T_FILE
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

// Struct for minishell
typedef struct s_shell
{
	int				env_size;
	int				exit;
	int				i;
	int				j;
	size_t			allocated_size;
	char			**env;
	char			*prompt;
	t_token			*cmd_list;
	int				input_fd;
	int				output_fd;
	int				prev_fd;
	pid_t			process_ids[100];
	int				process_count;
	int				last_return ;
	int				flag;
	int				signal_received;
	bool			end;
}					t_shell;

// builtin_cd
int					minishell_cd(t_shell *minishell);

// builtin_echo
void				minishell_echo(t_shell *minishell);

// builtin_env
int					minishell_env(t_shell *minishell);

// builtin_exit
void				minishell_exit(t_shell *minishell, int exit_code);

// builtin_export_utils_1
void				env_realloc(t_shell *minishell);
void				print_vars(t_shell *minishell);
char				*string_concat(char **strings, char *joined,
						int start_index);
char				*join_from_index(char **cmd, int start_index);

// builtin_export_utils_2
char				*get_var_name(const char *content);
int					is_valid_identifier(const char *str);
void				create_env_entry(char *dest, const char *var_name,
						const char *var_value);

//builtin_export_utils_3
int					save_var(t_shell *minishell, char *content);

// builtin_export
int					minishell_export(t_shell *minishell);

// builtin_pwd
void				minishell_pwd(void);

// builtin_unset
int					search_env(t_shell *minishell, char *var);
int					minishell_unset(t_shell *minishell);

// parser(join_tokens)
void				join_identifier_tokens(t_token *lst);

// parser(parse_single_quotes)
void				parse_single_quotes(t_token *token);

// parser(parse_double_quotes)
void				parse_double_quotes(t_token *token, t_shell *minishell);

// parser(parse_double_quotes_utils_1)
char				*prepend_dollar(const char *var_name);
void				append_to_result(char **result, t_shell *minishell,
						const char *str);
void				handle_variable_value(char **result, t_shell *minishell,
						char *var_value);
void				handle_variable_not_found(char **result, t_shell *minishell,
						const char *var_name);

// parser(parse_double_quotes_utils_2)
void				extract_var_name(char *str, t_shell *minishell,
						char *var_name, int *var_len);
void				handle_digit_case(char *str, char **result,
						t_shell *minishell);
void				remove_trailing_double_quote(char **result,
						t_shell *minishell);
void				handle_env_variable_expansion(char *str, char **result,
						t_shell *minishell);

// parser(parse_double_quotes_utils_3)
void				handle_special_env_variable(char *result,
						t_shell *minishell);
void				extract_variable_name(char *str, char **var_name,
						int *var_len);
void				handle_regular_env_variable(char *str, char *result,
						t_shell *minishell);
void				handle_env_variable_expansion(char *str, char **result,
						t_shell *minishell);

// parser (parse_double_quotes_utils_4)
void				process_exit_status(char **result, t_shell *minishell);
void				process_special_characters(char *str, char **result,
						t_shell *minishell);
void				process_dollar_followed_by_quote(char **result,
						t_shell *minishell);
void				process_special_dollar_cases(char *str, char **result,
						t_shell *minishell);
void				process_dollar_character(char *str, char **result,
						t_shell *minishell);

// parser (parse_double_quotes_utils_5)
void				update_parse_variables(int *len, char **result);
void				initialize_parse_variables(t_token *token,
						t_shell *minishell);
void				process_character(char *str, char **result,
						t_shell *minishell);

// parser (parse_semicolon)ls
void				parse_semicolon(t_token *token);

// parser (parse_value)
void				handle_env_variable(t_token *curr, t_shell *minishell);
void				handle_exit_status(t_token *curr, t_shell *minishell);
void				handle_exit_status_with_suffix(t_token *curr,
						t_shell *minishell, const char *suffix);
void				process_token(t_token *curr, t_shell *minishell);
void				parse_value(t_token *token_lst, t_shell *minishell);

// parser_utils
void				handle_character(char **command, char *input,
						int *inside_quote, int i);
int					handle_unclosed_quote(t_shell *minishell, char **command,
						int *inside_quote);
void				process_input(char **command, char *input,
						int *inside_quote, t_shell *minishell);
void				finalize_command(t_token *token, char *command);
void				parse_unclosed(t_token *token, t_shell *minishell);

// parser
void				set_token_pointers(t_token *tokens);
void				handle_token_parsing(t_token *token, t_shell *minishell);
int					check_unclosed(t_token *token);
void				parse_token(t_token *token, t_shell *minishell);
t_token				*token_parser(t_token *token_lst, t_shell *minishell);

// parser (remove_embedded_quotes)
void				remove_embedded_quotes(t_token *token);
int					find_first_quote(char *str, int len);
int					find_last_quote(char *str, int len, int first_quote_index,
						char quote_char);

int					check_quotes_in_between(char *str, int first_quote_index,
						int last_quote_index, char quote_char);
char				*remove_quotes(char *str, int first_quote_index,
						int last_quote_index, int len);

// parser (remove_embedded_quotes_utils)
void				update_token_if_needed(t_token *token, char *new_str);
void				free_and_replace_token(t_token *token, char *new_str);

// pipex (execute_utils)
int					check_command(char *cmd, t_shell *minishell);
char				**get_command_array(char *cmd, t_shell *minishell);
char				*get_command_path(char **s_cmd, t_shell *minishell);
void				exec_cmd(t_token *curr, t_shell *minishell);

// pipex (execute_utils1)
void				load_previous_fd_to_stdin(t_shell *minishell);
void				load_previous_fd_to_stdout(t_shell *minishell);
t_token				*update_curr_pointer(t_token *curr, int flag, int i);

// pipex (execute)
void				execute_single_command(t_token *curr, t_shell *minishell);
void				execute_pipeline(t_token *curr, t_shell *minishell);
void				execute_with_redirection(t_token *token, t_shell *minishell,
						int index);
void				execute_builtin_or_exec_exit(t_token *curr,
						t_shell *minishell);
void				execute_builtin_or_exec(t_token *curr, t_shell *minishell);

// pipex (execute1)
void				execute_command_with_redir(t_token *curr,
						t_shell *minishell);
void				handle_redir_child_process(t_token *curr,
						t_shell *minishell, t_token *redir_token);
void				handle_redir_parent_process(t_shell *minishell, int pid);
t_token				*get_redir_token(t_token *curr, t_shell *minishell);
t_token 			*execute_with_redir(t_token *curr, t_shell *minishell);
void				execute_redir_with_pipe(t_token *curr, t_shell *minishell);

// pipex (utils_1)
int					num_of_commands(t_shell *minishell);
int					num_of_pipes(t_shell *minishell);
int					num_of_args_or_file(t_shell *minishell);
int					num_of_redirections(t_shell *minishell);
t_token				*move_lst_by_index(t_token *curr, int index);

// pipex (utils_2)
int					check_redirection_type(t_token *curr);
int					check_for_redirections(t_shell *minishell);
int					num_of_args(t_shell *minishell);

// pipex (utils_3)
void				ft_free_tab(char **tab);
void				ft_free_two_tabs(char **tab1, char **tab2);
char				*get_path(char *cmd, t_shell *minishell);

// pipex (utils_4)
void				exit_handler(int exit_code);
int					open_file(const char *file, int mode);
void				restore_fds(int input_fd, int output_fd);

// pipex
int					handle_redirection(t_shell *minishell, t_token *curr);
t_token				*handle_builtins(t_token *curr, t_shell *minishell);
void				pipex(t_shell *minishell);

// tokenizer (create_token)
t_token				*create_token(char *token, t_token_type type);
void				token_add_back(t_token **head, char *token,
						t_token_type type);
void				free_tokenlst(t_token *head);

// tokenizer (tokenizer_utils_1)
size_t				ft_wordlen(const char *s, char c);
int					add_symbol_lst(char **line, t_token_type type,
						t_token **token_lst);
void				handle_special_case(char **line, t_token **token_lst,
						t_shell *minishell);
int					add_command_lst(char **line, t_token **token_lst);

// tokenizer (tokenizer_utils_2)
void				print_tokenlst(t_token *token_lst);
void				append_rest_of_line(char **line, char *result,
						t_token **token_lst);
void				handle_special_case(char **line, t_token **token_lst,
						t_shell *minishell);

// tokenizer (tokenizer_utils_3)
char				*allocate_and_copy_result(const char *source);
void				handle_expansion(char **line, char *expanded,
						t_token **token_lst);
void				handle_variable_expansion(char **line, char *start,
						t_token **token_lst, t_shell *minishell);
void				handle_environment_variable(char **line,
						t_token **token_lst, t_shell *minishell);

// tokenizer (tokenizer_utils_4)
void				handle_remaining_text(char **line, t_token **token_lst);
void				handle_backslash(char **line, t_token **token_lst);
void				add_quoted_content_to_token_list(char *start, char **line,
						t_token **token_lst);
void				handle_variable_expansion(char **line, char *start,
						t_token **token_lst, t_shell *minishell);

// tokenizer (tokenizer_utils_5)
int					ft_iswhitespace(char *line);
int					ft_isbackslash(char *line);
int					ft_issemicolon(char *line);
char				*ft_copy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);

// tokenizer
void				add_literal_quote_to_token_list(char quote_type,
						t_token **token_lst);
void				handle_quotes(char **line, t_token **token_lst);
t_token				*token_processor(char *line, t_shell *minishell);

// env_manager (utils)
char				*get_env_value(t_shell *minishell, const char *var,
						int return_empty);
int					env_len(t_shell *minishell);
int					search_env_by_var(t_shell *minishell, const char *var);

// env_manager
void				sort_env(t_shell *minishell);
void				set_env_entry(t_shell *minishell, char *new_entry, int idx);
void				set_env(t_shell *minishell, const char *var,
						const char *value);
void				init_env(t_shell *minishell, char **envp);

// error_msg_utils
char				*ft_strjoin_free(char **s1, char const *s2);
void				delete_command(void *elem);
void				free_and_exit(t_shell *minishell, int return_value);

// error_msg
int					minishell_error_msg(char *cmd, int error_no);

// execute_commands_utiils.c
int					check_builtin(char *s);
int					count_tokens(t_shell *minishell);
void				handle_exit_command(t_token *curr, t_shell *minishell);

// execute_commands.c
int					execute_builtin_1(t_token *curr, t_shell *minishell);
int					execute_builtin_2(t_token *curr, t_shell *minishell);
int					other_cmds(t_token *curr, t_shell *minishell);

// free_shell
void				free_env(char **env);
void				free_shell(t_shell *minishell);

// history
void				prompt(void);
int					print_history(void);
int					hist_feature(const char *s);

// main.c
char				*read_input_line(t_shell *g_shell);
void				process_command_line(t_shell *minishell, char *line);
void				main_loop(t_shell *g_shell);

// redirect utils
char				*join_and_free(char *s1, const char *s2);
char				*expand_env_variable(char *str, t_shell *minishell);
int					read_input(char **str, char *delimiter, int i,
						t_shell *minishell);
int					is_delimiter(const char *str, const char *delimiter);
void				signal_exit(int signal_number);
void				error_eof(char *end_of_file, int i);

// redirect
int					execute_parent(int pid, int *pipe_des);
int					here_doc(t_shell *minishell, char *delimiter, int i);
int					redirect_input(t_shell *minishell, t_token *curr);
int					redirect_output(t_shell *minishell, t_token *curr);

// shell
t_shell				*init_shell(void);
void				reset_process_ids(t_shell *minishell);
void				free_shell(t_shell *minishell);
void				initialize_shell(t_shell **minishell, char **envp);
void				cleanup(t_shell *g_shell);

// signals
void				sigint_handler(int signal);
void				sigint_handler1(int signal);
void				sigquit_handler(int signal);
void				setup_signal_handler(void);

// sutils_1
char				**ft_dqsplit(char const *s, char c);
void				convert_cmd(char **s);

// sutils_2
void				*ft_realloc(void *ptr, size_t new_size);
void				reset_minishell(t_shell *minishell);

#endif
