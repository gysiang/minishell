/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/23 23:19:33 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***
for (int i = 0; s[i] != NULL; i++) {
	printf("av[%d]: %s\n", i, s[i]);
}; **/

/***
void	pipex(char *input, char **env)
{
	int		n;
	int		i;
	char	**command;

	command = ft_dqsplit(input, ' ');
	convert_cmd(command);
	i = 0;
	n = 0;
	while (command[n] != NULL)
		n++;
	while (i < n - 1)
	{
		do_pipe(command[i++], env);
	}
	exec_cmd(command[i], env);
} **/

void	pipex(t_token *token_lst, char **env)
{
	int		i;
	int		num_of_command;
	t_token	*curr_token;
	char	**command;

	curr_token = token_lst;
	num_of_command = 0;
	while (curr_token != NULL)
	{
		if (curr_token->type == T_IDENTIFIER)
			num_of_command++;
		curr_token = curr_token->next;
	}
	command = (char **)malloc((num_of_command + 1) * sizeof(char *));
	if (!command)
		exit(EXIT_FAILURE);
	i = 0;
	curr_token = token_lst;
	while (i < num_of_command)
	{
		if (curr_token->type == T_IDENTIFIER)
		{
			command[i++] = curr_token->token;
		 	printf("command[%d]: %s\n", i, curr_token->token);
		}
		curr_token = curr_token->next;
	}
	command[num_of_command] = NULL;
	i = 0;
	while (i < num_of_command - 1)
	{
		do_pipe(command[i++], env);
	}
	exec_cmd(command[num_of_command - 1], env);
	free(command);
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
		//printf("This is user input: %s\n", line);
		token_lst = token_processor(line);
		//print_tokenlst(token_lst);
		if (hist_feature(line) == 1)
			return (1);
		/**
		for (int i = 0; av_str[i] != NULL; i++) {
			printf("av[%d]: %s\n", i, av_str[i]);
		} **/
		pipex(token_lst, env);
		free(line);
	}
	return (0);
}
