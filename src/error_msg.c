/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:35:43 by axlee             #+#    #+#             */
/*   Updated: 2024/05/20 13:15:07 by axlee            ###   ########.fr       */
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

int minishell_error_msg(char *cmd, int error_no) {
    char *error;
    int return_no;
    char *error_msg;

    error = ft_strdup("minishell: ");
    error = ft_strjoin_free(&error, cmd);
    error = ft_strjoin_free(&error, ": ");
    
    // Specific error messages
    if (error_no == 42) {
        error_msg = ft_strdup("command not found");
    } else if (error_no == EISDIR) {
        error_msg = ft_strdup("Is a directory");
    } else if (error_no == ENOENT) {
        error_msg = ft_strdup("No such file or directory");
    } else if (error_no == EACCES) {
        error_msg = ft_strdup("Permission denied");
    } else {
        error_msg = ft_strdup(strerror(error_no));
    }
    
    error = ft_strjoin_free(&error, error_msg);
    free(error_msg);
    ft_putendl_fd(error, 2);
    free(error);

    // Map specific errors to their corresponding exit codes
    if (error_no == 42) {  // "command not found"
        return_no = 127;
    } else if (error_no == ENOENT) {  // "No such file or directory"
        return_no = 127;
    } else if (error_no == EISDIR) {  // "Is a directory"
        return_no = 126;
    } else if (error_no == EACCES) {  // "Permission denied"
        return_no = 126;
    } else {
        return_no = 1;  // General error
    }

    return return_no;
}