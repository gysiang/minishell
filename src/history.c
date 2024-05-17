/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:49:27 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/17 15:14:23 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	printf("minishell$");
	usleep(5000);
}

void	print_history(void)
{
	HIST_ENTRY	**mylist;
	int			i;

	mylist = history_list();
	i = 0;
	if (!mylist)
	{
		printf("Error getting history list\n");
		return ;
	}
	while (mylist[i] != NULL)
	{
		printf("%d: %s\n", i + 1, mylist[i]->line);
		i++;
	}
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
