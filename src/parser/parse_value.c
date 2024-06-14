/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:54:35 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/14 12:57:43 by axlee            ###   ########.fr       */
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
		return;
	result[0] = '\0';

	// Skip the '$' character
	//token++;

	// Extract the variable name
	var_name = ft_strdup(token);

	// Get the environment variable value
	env_value = get_env_value(minishell, var_name);

	// If the environment variable is not set, use an empty string
	if (!env_value)
		env_value = ft_strdup("");

	// Append the environment variable value to the result
	append_to_result(&result, minishell, env_value);
	free(env_value);

	// Free the old token and set the new expanded token
	free(curr->token);
	curr->token = result;

	// Free the variable name if it was allocated
	free(var_name);
}
/*void	handle_env_variable(t_token *curr, t_shell *minishell)
{
	char	*result;
	char	*env_value;
	char	*exit_status_str;
	int		exit_status;

	result = ft_substr(curr->token, 1, ft_strlen(curr->token) - 1);
	if (!result)
		return ;
	env_value = get_env_value(minishell, result);
	free(result);
	if (!env_value)
		env_value = ft_strdup("");
	free(curr->token);
	curr->token = env_value;
}*/
void	handle_exit_status(t_token *curr, t_shell *minishell)
{
	char	*exit_status_str;
	int		exit_status;

	exit_status = minishell->last_return ;
	exit_status_str = ft_itoa(exit_status);
	free(curr->token);
	curr->token = exit_status_str;
}

void	handle_exit_status_with_suffix(t_token *curr, t_shell *minishell,
		const char *suffix)
{
	char	*exit_status_str;
	char	*new_token;
	int		exit_status;

	exit_status = minishell->last_return ;
	exit_status_str = ft_itoa(exit_status);
	new_token = ft_strjoin(exit_status_str, suffix);
	free(curr->token);
	curr->token = new_token;
	free(exit_status_str);
}

/*static void	handle_literal_string(t_token *curr, t_shell *minishell)
{
	char	*result;
	char	*token;
	t_token	*curr;
	char	*token;

	token = curr->token;
	result = malloc(1);
	result[0] = '\0';
	while (*token)
	{
		append_to_result(&result, minishell, token);
		token++;
	}
	free(curr->token);
	curr->token = result;
}*/
void	parse_value(t_token *token_lst, t_shell *minishell)
{
	t_token	*curr;
	char	*token;

	curr = token_lst;
	while (curr != NULL)
	{
		token = curr->token;
		if (token == NULL || token[0] != '$')
		{
			curr = curr->next;
			continue ;
		}
		if (token[0] == '$')
		{
			if (ft_strcmp(token, "$") == 0)
			{
				curr = curr->next;
				continue ;
			}
			else if (ft_strcmp(token, "$?") == 0)
			{
				handle_exit_status(curr, minishell);
			}
			else if (ft_strncmp(token, "$?", 2) == 0)
			{
				handle_exit_status_with_suffix(curr, minishell, token + 2);
			}
			else
			{
				handle_env_variable(curr, minishell);
			}
		}
		curr = curr->next;
	}
}

/*void	parse_value(t_token *token_lst, t_shell *minishell)
{
	t_token	*curr;
	char	*token;

	curr = token_lst;
	while (curr != NULL)
	{
		token = curr->token;
		if (token == NULL || token[0] != '$')
		{
			curr = curr->next;
			continue ;
		}
		if (ft_strcmp(token, "$") == 0)
		{
			curr = curr->next;
			continue ;
		}
		else if (ft_strcmp(token, "$?") == 0)
			handle_exit_status(curr, minishell);
		else if (ft_strncmp(token, "$?", 2) == 0)
			handle_exit_status_with_suffix(curr, minishell, token + 2);
		else
			handle_env_variable(curr, minishell);
		curr = curr->next;
	}
}*/

/*void	parse_value(t_token *token_lst, t_shell *minishell)
{
	t_token	*curr;
	char	*token;

	curr = token_lst;
	token = curr->token;
	if (token == NULL || token[0] != '$')
		return ;
	if (ft_strcmp(token, "$") == 0)
		return ;
	else if (ft_strcmp(token, "$?") == 0)
		handle_exit_status(curr, minishell);
	else if (ft_strncmp(token, "$?", 2) == 0)
		handle_exit_status_with_suffix(curr, minishell, token + 2);
	else
		handle_env_variable(curr, minishell);
}*/
