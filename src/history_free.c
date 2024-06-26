/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 02:53:36 by axlee             #+#    #+#             */
/*   Updated: 2024/06/27 03:27:33 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_history_entries(t_history *history)
{
	int	i;

	if (history && history->entries)
	{
		i = 0;
		while (i < history->count)
		{
			free(history->entries[i]);
			i++;
		}
		free(history->entries);
		history->entries = NULL;
	}
}

void	ft_free_history(t_shell *minishell)
{
	if (minishell->history)
	{
		free_history_entries(minishell->history);
		free(minishell->history);
		minishell->history = NULL;
	}
}

void	ft_using_history(t_shell *minishell)
{
	t_history	*history;
	int			i;

	i = 0;
	history = (t_history *)malloc(sizeof(t_history));
	if (!history)
	{
		perror("malloc");
		return ;
	}
	history->capacity = 100;
	history->entries = (char **)malloc(sizeof(char *) * history->capacity);
	if (!history->entries)
	{
		free(history);
		perror("malloc");
		return ;
	}
	while (i < history->capacity)
	{
		history->entries[i] = NULL;
		i++;
	}
	history->count = 0;
	minishell->history = history;
}

void	add_to_history(t_shell *minishell, const char *line)
{
	if (minishell->history->count >= minishell->history->capacity)
	{
		minishell->history->capacity *= 2;
		minishell->history->entries = ft_realloc(minishell->history->entries,
				sizeof(char *) * minishell->history->capacity);
		if (!minishell->history->entries)
		{
			perror("realloc");
			return ;
		}
	}
	minishell->history->entries[minishell->history->count] = ft_strdup(line);
	if (!minishell->history->entries[minishell->history->count])
	{
		perror("strdup");
		return ;
	}
	minishell->history->count++;
}
