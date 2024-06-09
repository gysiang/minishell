/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:54:35 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/09 11:06:26 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_semicolon(t_token *token)
{
	t_token	*curr;
	char	*result;
	size_t	len;

	curr = token;
	len = ft_wordlen(curr->token, ';');
	result = (char *)malloc(len + 1);
	if (!result)
		return ;
	ft_copy(result, curr->token, len);
	free(curr->token);
	curr->token = result;
}

void	handle_env_variable(t_token *curr, t_shell *minishell)
{
	char	*result;
	char	*env_value;

	result = ft_substr(curr->token, 1, ft_strlen(curr->token) - 1);
	if (!result)
		return ;
	env_value = get_env_value(minishell, result);
	free(result);
	if (!env_value)
		env_value = ft_strdup(" ");
	free(curr->token);
	curr->token = env_value;
}

void handle_exit_status(t_token *curr, t_shell *minishell)
{
    char *exit_status_str;
    int exit_status;

    exit_status = minishell->last_return;
    exit_status_str = ft_itoa(exit_status);
    free(curr->token);
    curr->token = exit_status_str;
}

void handle_exit_status_with_suffix(t_token *curr, t_shell *minishell, const char *suffix)
{
    char *exit_status_str;
    char *new_token;
    int exit_status;

    exit_status = minishell->last_return;
    exit_status_str = ft_itoa(exit_status);
    new_token = ft_strjoin(exit_status_str, suffix);
    free(curr->token);
    curr->token = new_token;
    free(exit_status_str);
}

void parse_value(t_token *token_lst, t_shell *minishell)
{
    t_token *curr;
    char *token;

    curr = token_lst;
    token = curr->token;

    if (token == NULL || token[0] != '$')
        return;
    if (ft_strcmp(token, "$") == 0)
        return;
    else if (ft_strcmp(token, "$?") == 0)
        handle_exit_status(curr, minishell);
    else if (ft_strncmp(token, "$?", 2) == 0)
        handle_exit_status_with_suffix(curr, minishell, token + 2);
    else
        handle_env_variable(curr, minishell);
}
