/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/11 14:12:05 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (!s1[i] && !s2[i])
		return (0);
	return (1);
}

void	prompt()
{
	printf("minishell$");
	fflush(stdout);
	usleep(5000);
}

void	print_history()
{
	//HISTORY_STATE *myhist = history_get_history_state();
	HIST_ENTRY	**mylist = history_list();
	int	i;

	i = 0;
	if (!mylist)
	{
		printf("Error getting history list\n");
		return ;
	}
	while (1)
	{
		if (mylist[i] != NULL)
			printf("%d: %s\n", i + 1, mylist[i]->line);
		else
			break ;
		i++;
	}
}
int	main()
{
	char	*input;

	using_history();
	while (1)
	{
		prompt();
		input = readline(" ");
		if (input != NULL || *input != '\0')
		{
			printf("This is user input: %s\n", input);
			add_history(input);
			if (ft_strcmp(input, "history") == 0)
			{
				print_history();
			}
			if (ft_strcmp(input, "history -c") == 0)
			{
				clear_history();
			}
		}
		free(input);
	}
	return (0);
}
