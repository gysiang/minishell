/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/19 14:41:26 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

void	pipex_feature(char *input, char **env)
{
	int		p_fd[2];
	pid_t	pid;
	char	**s;

	s = ft_dqsplit(input, ' ');
	convert_cmd(s);
	/***
	for (int i = 0; s[i] != NULL; i++) {
		printf("av[%d]: %s\n", i, s[i]);
	}; **/
	if (pipe(p_fd) == -1)
	{
		ft_putstr_fd("Error creating pipe\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	//printf("entered in child process\n");
	if (pid == 0)
		child(s, p_fd, env);
	else if (pid > 0)
	{
		waitpid(pid, NULL, WNOHANG);
		//printf("entered in parent process\n");
		parent(s, p_fd, env);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	//return (1);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*line;
	t_token *token_lst;

	using_history();
	setup_signal_handler();
	while (1)
	{
		//prompt();
		line = readline(PROMPT);
		if (line == NULL)
		{
			printf("exit\n");
			break;
		}
		if (*line == '\0')
			continue;
		printf("This is user input: %s\n", line);
		token_lst = token_processor(line);
		print_tokenlst(token_lst);
		if (hist_feature(line) == 1)
			return (1);
		/**
		for (int i = 0; av_str[i] != NULL; i++) {
			printf("av[%d]: %s\n", i, av_str[i]);
		} **/
		pipex_feature(line, env);
		free(line);
	}
	return (0);
}
