/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/14 17:56:11 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/minishell.h"

void	pipex_feature(char *input, char **env)
{
	int		p_fd[2];
	pid_t	pid;
	char	**s;

	s = ft_dqsplit(input, ' ');
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
	char	*input;

	using_history();
	setup_signal_handler();
	while (1)
	{
		prompt();
		input = readline(" ");
		if (input == NULL)
		{
			printf("exit\n");
			break;
		}
		if (*input == '\0')
			//free(input);
			continue;
		printf("This is user input: %s\n", input);
		if (hist_feature(input) == 1)
			return (1);
		// Print all av string
		/**
		for (int i = 0; av_str[i] != NULL; i++) {
			printf("av[%d]: %s\n", i, av_str[i]);
		} **/
		pipex_feature(input, env);
		free(input);
	}
	return (0);
}
