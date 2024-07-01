/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:05:01 by axlee             #+#    #+#             */
/*   Updated: 2024/07/01 14:53:17 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_export_tokens(t_token *current, t_shell *minishell)
{
	int	result;

	result = 0;
	while (current)
	{
		if (current->type != T_IDENTIFIER)
			break ;
		result = save_var(minishell, current->token);
		if (result != 0)
			return (result);
		current = current->next;
	}
	return (result);
}

static void	execute_export_to_file(t_shell *minishell, const char *filename)
{
	int	tmp_file;
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	tmp_file = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (tmp_file == -1)
	{
		perror("open");
		return ;
	}
	if (dup2(tmp_file, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(tmp_file);
		return ;
	}
	print_vars(minishell);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2");
	}
	safe_close(&saved_stdout);
	safe_close(&tmp_file);
	minishell->prev_fd = open(filename, O_RDONLY);
}

int	minishell_export(t_shell *minishell)
{
	t_token	*current;

	if (!minishell || !minishell->cmd_list)
	{
		printf("No command list provided.\n");
		return (0);
	}
	current = minishell->cmd_list->next;
	if (!current)
	{
		print_vars(minishell);
		return (0);
	}
	if (current->type == T_PIPE)
	{
		execute_export_to_file(minishell, "tmp");
		return (0);
	}
	return (process_export_tokens(current, minishell));
}
