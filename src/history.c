/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:49:27 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/11 21:03:30 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt()
{
	printf("minishell$");
	fflush(stdout);
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

void	hist_feature(const char *s)
{
	add_history(s);
	if (ft_strcmp(s, "history") == 0)
		print_history();
	if (ft_strcmp(s, "history -c") == 0)
		clear_history();
}