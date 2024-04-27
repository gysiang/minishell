/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:39:49 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/12 12:25:06 by axlee            ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <limits.h>

// Struct for commands

typedef struct s_cmd
{
	t_uchar	type;
	int	argc;
	char	**argv;
	t_list	*input;
	t_list	*output;
	int	return_value;
}		t_cmd;

/*
 * Struct for Minishell
*/

typedef struct s_shell
{
	int	env_size;
	char	**env;
	char	**pwd;
	char	*prompt;
	char	*home;
	t_list	*cmd_list;
	int	data_fd[2];
	int	ret_fd[2];
	int	last_return;
	t_bool	end;
}		t_shell;


/* 
 * Builtin C Functions
* */

// Error Message
int minishell_error_msg(char *cmd, int error_no);

int	minishell_echo(t_shell *minishell, t_cmd *cmd);

// utils
void	put_string_fd(int fd, const char *s);

// signals
void	sigint_handler(int signal);
void	setup_signal_handler();

//history
void	print_history();
void	prompt();
void	hist_feature(const char *s);

#endif
