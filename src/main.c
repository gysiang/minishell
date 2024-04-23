/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/23 13:20:35 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***
for (int i = 0; s[i] != NULL; i++) {
	printf("av[%d]: %s\n", i, s[i]);
}; **/

void	pipex_feature(char *input, char **env)
{
	int		p_fd[2];
	int		num_of_commands;
	int		i;
	char	**command;

	if (pipe(p_fd) == -1)
		exit(EXIT_FAILURE);
	command = ft_dqsplit(input, ' ');
	convert_cmd(command);
	i = 0;
	num_of_commands = 0;
	while (command[num_of_commands] != NULL)
		num_of_commands++;
	while (i < num_of_commands - 1)
	{
		do_pipe(command[i], p_fd, env);
		i++;
	}
	exec_cmd(command[i], env);
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
