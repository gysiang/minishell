/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:35:43 by axlee             #+#    #+#             */
/*   Updated: 2024/05/17 14:54:56 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char **s1, char const *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	if (!*s1)
	{
		*s1 = ft_strdup("");
		if (!*s1)
			return (NULL);
	}
	result = ft_strjoin(*s1, s2);
	free(*s1);
	*s1 = NULL;
	return (result);
}

void	delete_command(void *elem)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)elem;
	ft_split_free(&cmd->argv);
	ft_lstclear(&cmd->input, free);
	ft_lstclear(&cmd->output, free);
	free(cmd);
}

void	free_and_exit(t_shell *minishell, int return_value)
{
	rl_clear_history();
	ft_split_free(&minishell->env);
	ft_lstclear((t_list **)&(minishell->cmd_list), delete_command);
	free(minishell->prompt);
	exit(return_value);
}

char	*error_messages(int i)
{
	static const char	*error_msg[] = {
		"minishell: %s: command not found",
		"minishell: %s: No such file or directory",
		"minishell: %s: Is a directory",
		"minishell: %s: Permission denied"};

	if (i >= 0 && i <= 3)
		return (error_msg[i]);
	else
		return (NULL);
}

int	minishell_error_msg(char *cmd, int error_no)
{
	char	*error;
	int		return_no;

	error = ft_strdup("minishell: ");
	error = ft_strjoin_free(&error, cmd);
	error = ft_strjoin_free(&error, ": ");
	if (error_no >= 0 && error_no <= 3)
	{
		error = ft_strjoin_free(&error, error_messages(error_no));
	}
	else
	{
		error = ft_strjoin_free(&error, strerror(error_no));
	}
	ft_putendl_fd(ft_itoa(error_no), 2);
	free(error);
	if (error_no == 0 || error_no == -1)
		return_no = 127;
	else
		return_no = 126;
	return (return_no);
}
