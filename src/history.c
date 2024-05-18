/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:49:27 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/17 23:32:51 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	printf("minishell$");
	usleep(5000);
}

int	print_history(void)
{
	HIST_ENTRY	**mylist;
	int			i;

	mylist = history_list();
	i = 0;
	if (!mylist)
	{
		printf("Error getting history list\n");
		return (0);
	}
	while (mylist[i] != NULL)
	{
		printf("%d: %s\n", i + 1, mylist[i]->line);
		i++;
	}
	return (0);
}

int	hist_feature(const char *s)
{
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
