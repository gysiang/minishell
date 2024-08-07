/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:54:35 by gyong-si          #+#    #+#             */
/*   Updated: 2024/07/03 19:43:40 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_env_variable(t_token *curr, t_shell *minishell)
{
	char	*result;
	char	*env_value;
	char	*token;
	char	*var_name;

	token = curr->token;
	result = malloc(1);
	if (!result)
		return ;
	result[0] = '\0';
	token++;
	while (*token)
	{
		var_name = ft_strdup(token);
		env_value = get_env_value(minishell, var_name, 1);
		if (!env_value)
			env_value = ft_strdup("");
		append_to_result(&result, minishell, env_value);
		free(env_value);
		free(var_name);
		token++;
	}
	free(curr->token);
	curr->token = result;
}

void	handle_exit_status(t_token *curr, t_shell *minishell)
{
	char	*exit_status_str;

	exit_status_str = ft_itoa(minishell->last_return);
	free(curr->token);
	curr->token = exit_status_str;
}

void	handle_exit_status_with_suffix(t_token *curr, t_shell *minishell,
		const char *suffix)
{
	char	*exit_status_str;
	char	*result;

	exit_status_str = ft_itoa(minishell->last_return);
	result = ft_strjoin(exit_status_str, suffix);
	free(exit_status_str);
	free(curr->token);
	curr->token = result;
}

void	process_token(t_token *curr, t_shell *minishell)
{
	char	*token;

	token = curr->token;
	if (token == NULL || token[0] != '$')
		return ;
	if (ft_strcmp(token, "$") == 0)
		return ;
	if (ft_strcmp(token, "$?") == 0)
		handle_exit_status(curr, minishell);
	else if (ft_strncmp(token, "$?", 2) == 0)
		handle_exit_status_with_suffix(curr, minishell, token + 2);
	else
		handle_env_variable(curr, minishell);
}

void	parse_value(t_token *token_lst, t_shell *minishell)
{
	t_token	*curr;

	curr = token_lst;
	while (curr != NULL)
	{
		process_token(curr, minishell);
		curr = curr->next;
	}
}
