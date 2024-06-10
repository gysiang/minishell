/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:54:08 by axlee             #+#    #+#             */
/*   Updated: 2024/06/10 11:54:26 by axlee            ###   ########.fr       */
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