/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:54:35 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/17 14:29:34 by axlee            ###   ########.fr       */
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

/*void handle_env_variable(t_token *curr, t_shell *minishell)
{
	char	*result;
	char	*env_value;
	char	*token;
	char	*var_name;
	char	*result;
	char	*env_value;
	char	*token;
	char	*var_name;
	char	*exit_status_str;
	int		exit_status;

	printf("handle env value\n");
	token = curr->token;
	result = malloc(1);
	if (!result)
		return ;
	result[0] = '\0';
	// Skip the '$' character
	token++;
	if (ft_strcmp(token, "") == 0) {
		append_to_result(&result, minishell, "$");
	} else {
		var_name = ft_strdup(token);
		env_value = get_env_value(minishell, var_name, 1);
			// Pass 1 to return an empty string if not found
		if (!env_value)
			env_value = ft_strdup("");
		append_to_result(&result, minishell, env_value);
		free(env_value);
		free(var_name);
	}
	free(curr->token);
	curr->token = result;
}*/
/*void	handle_env_variable(t_token *curr, t_shell *minishell)
{
	printf("handle env value\n");
	token = curr->token;
	result = malloc(1);
	if (!result)
		return ;
	result[0] = '\0';
	// Skip the '$' character
	token++;
	var_name = ft_strdup(token);
	env_value = get_env_value(minishell, var_name, 1);
	if (!env_value)
		env_value = ft_strdup("");
	append_to_result(&result, minishell, env_value);
	free(env_value);
	free(curr->token);
	curr->token = result;
	free(var_name);
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

void	process_token(t_token *curr, t_shell *minishell)
{
	char	*token;

	token = curr->token;
	if (token == NULL || token[0] != '$')
		return ;
	if (ft_strcmp(token, "$") == 0)
		return ;
	if (ft_strcmp(token, "$?") == 0)
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
		if (token[0] == '$')
		{
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
		}
		curr = curr->next;
	}
}*/

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
