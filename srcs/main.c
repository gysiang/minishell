/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/12 16:42:48 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/minishell.h"

void	pipex_feature(char **s, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
	{
		ft_putstr_fd("Error creating pipe\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
		child(s, p_fd, env);
	else if (pid > 0)
	{
		waitpid(pid, NULL, WNOHANG);
		parent(s, p_fd, env);
	}
	close(p_fd[0]);
	close(p_fd[1]);
}

char **av_string(char *s)
{
	char **av;

	av = ft_dqsplit(s, ' ');
	return (av);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*input;
	char	**av_str;

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
		{
			free(input);
			continue;
		}
		printf("This is user input: %s\n", input);
		hist_feature(input);
		av_str = av_string(input);
		// Print all environment variables
		for (int i = 0; av_str[i] != NULL; i++) {
			printf("av[%d]: %s\n", i, av_str[i]);
		}
		pipex_feature(av_str, env);
		free(input);
	}
	return (0);
}
