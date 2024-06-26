/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:49:27 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/26 14:52:09 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fflush(void)
{
	char	buffer[1];

	buffer[0] = '\0';
	write(STDOUT_FILENO, buffer, 1);
}

void	prompt(void)
{
	printf("minishell$");
	ft_fflush();
}

void	ft_clear_history(t_shell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->history->count)
	{
		free(minishell->history->entries[i]);
		i++;
	}
	minishell->history->count = 0;
	minishell->history->current_index = 0;
}

int	ft_print_history(t_shell *minishell)
{
	int	i;

	if (!minishell->history || !minishell->history->entries)
	{
		printf("Error getting history list\n");
		return (0);
	}
	i = 0;
	while (i < minishell->history->count)
	{
		printf("%d: %s\n", i + 1, minishell->history->entries[i]);
		i++;
	}
	return (0);
}

int	hist_feature(const char *s, t_shell *minishell)
{
	if (ft_strcmp(s, "history") == 0)
	{
		ft_print_history(minishell);
		return (1);
	}
	if (ft_strcmp(s, "history -c") == 0)
	{
		ft_clear_history(minishell);
		return (1);
	}
	return (0);
}
