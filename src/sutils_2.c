/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sutils_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:36:40 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/27 23:15:35 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_get_size(char **array)
{
	size_t	size;

	size = 0;
	if (array == NULL)
		return (0);
	while (array[size] != NULL)
	{
		size++;
	}
	return (size);
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	size_t	old_size;
	void	*new_ptr;
	size_t	min_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	old_size = ft_get_size(ptr) * sizeof(char *);
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (old_size < new_size)
		min_size = old_size;
	else
		min_size = new_size;
	ft_memcpy(new_ptr, ptr, min_size);
	free(ptr);
	return (new_ptr);
}

void	reset_minishell(t_shell *minishell)
{
	minishell->process_count = 0;
	reset_process_ids(minishell);
	minishell->signal_received = 0;
	safe_close(&minishell->prev_fd);
	safe_close(&minishell->input_fd);
	safe_close(&minishell->output_fd);
	minishell->flag = 0;
	minishell->redir_no = 0;
}
