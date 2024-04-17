/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:49:27 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/14 16:04:36 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt()
{
	printf("minishell$");
	//fflush(stdout);
	usleep(5000);
}

void	print_history()
{
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

int	hist_feature(const char *s)
{
	add_history(s);
	if (ft_strcmp(s, "history") == 0)
	{
		print_history();
		return (1);
	}
	if (ft_strcmp(s, "history -c") == 0)
	{
		clear_history();
		return (1);
	}
	return (0);
}