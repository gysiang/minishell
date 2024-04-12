/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:22:41 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/12 12:25:03 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		open_file(char *file, int n);
char	*my_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);
void	exec_cmd(char *cmd, char **env);
void	ft_free_tab(char **tab);
void	exit_handler(int exit_code);
void	child(char **argv, int *p_fd, char **env);
void	parent(char **argv, int *p_fd, char **env);

#endif
