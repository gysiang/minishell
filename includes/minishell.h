/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:39:49 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/04 22:22:59 by gyong-si         ###   ########.fr       */
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

# define PROMPT "minishell$ "
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
	T_DOUBLEQUOTE
}	t_token_type;

// token structure
typedef struct	s_token
{
	char			*token;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Struct for commands
typedef struct s_cmd
{
	t_token_type	type;
	int				argc;
	char		**argv;
	t_list		*input;
	t_list		*output;
	int			return_value;
}	t_cmd;

/*
 * Struct for Minishell
*/

typedef struct s_shell
{
	int		env_size;
	char	**env;
	char	*user;
	char	*pwd;
	char	*home;
	char	*prompt;
	t_token	*cmd_list;
	int		data_fd[2];
	int		ret_fd[2];
	int		last_return;
	bool	end;
}	t_shell;

// Error Message
void    delete_command(void *elem);
void    free_and_exit(t_shell *minishell, int return_value);
int minishell_error_msg(char *cmd, int error_no);

// builtins
int	minishell_echo(t_shell *minishell, t_cmd *cmd);
int	minishell_exit(t_shell *minishell, t_cmd *cmd);
int minishell_export(t_shell *minishell, t_cmd *cmd);
int	minishell_unset(t_shell *minishell, t_cmd *cmd);
int minishell_cd(t_shell *minishell, t_cmd *cmd);
int	search_env(t_shell *minishell, char *var);
void    env_realloc(t_shell *minishell);
void	minishell_pwd(t_shell *minishell);
void	minishell_env(t_shell *minishell);

// utils
int	ft_strcmp(const char *s1, const char *s2);
char	**ft_dqsplit(char const *s, char c);
void	convert_cmd(char **s);

// ENV_Manager
char    *get_env(t_shell *minishell, const char *var);
int env_len(t_shell *minishell);
int search_env_by_var(t_shell *minishell, const char *var);
void  sort_env(t_shell *minishell);
void    init_env(t_shell *minishell, const char **envp);

// redirect
void    redirect(t_shell *minishell, t_cmd *cmd, int *redir);
int here_doc(t_shell *minishell, char *delimiter);

// signals
void	sigint_handler(int signal);
void	setup_signal_handler();

//history
void	print_history();
void	prompt();
int	hist_feature(const char *s);

void    delete_command(void *elem);
void    free_and_exit(t_shell *minishell, int return_value);
char *ft_strjoin_free(char **s1, char const *s2);
int minishell_error_msg(char *cmd, int error_no);


// tokenizer
void	token_add_back(t_token **head, char *token, t_token_type type);
void	free_tokenlst(t_token *head);
void	print_tokenlst(t_token *token_lst);
int	ft_iswhitespace(char *line);
int	ft_isbackslash(char *line);
int	add_symbol_lst(char **line, t_token_type type, t_token **token_lst);
int	add_command_lst(char **line, t_token **token_lst);
char	*ft_copy(char *dest, const char *src, size_t n);
char	*ft_strcat(char *dest, const char *src);
size_t	ft_wordlen(const char *s, char c);
t_token *create_token(char *token, t_token_type type);
t_token	*token_processor(char *line, t_shell *minishell);

// parser
void	join_identifier_tokens(t_token *lst);
t_token *token_parser(t_token *token_lst, t_shell *minishell);

//pipex

int		open_file(char *file, int n);
char	*my_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);
void	exec_cmd(char *cmd, char **env);
void	ft_free_tab(char **tab);
void	exit_handler(int exit_code);
void	pipex(t_token *token_lst, char **env);
void	child(char *command, int *p_fd, char **env);
void 	parent(int *p_fd);
void	do_pipe(char *command, char **env);


#endif
