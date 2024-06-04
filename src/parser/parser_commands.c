/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:54:35 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/04 04:38:05 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_single_quotes(t_token *token)
{
    char *str;
    int len;
    char *result;

    str = token->token;
    len = ft_strlen(str);
    result = malloc(len - 1); // Allocate memory for the string without quotes
    if (!result)
        return;
    if (len > 1 && str[0] == '\'' && str[len - 1] == '\'')
    {
        ft_memcpy(result, str + 1, len - 2); // Copy the string without the quotes
        result[len - 2] = '\0';
        token->is_single_quoted = 1;
    }
    else 
    {
        ft_strcpy(result, str);
        token->is_single_quoted = 0;
    }
    free(token->token);
    token->token = result;
}

void parse_double_quotes(t_token *token)
{
    char *str;
    int len;
    char *result;

    str = token->token;
    len = ft_strlen(str);
    result = malloc(len - 1); // Allocate memory for the string without quotes
    if (!result)
        return;
    if (len > 1 && str[0] == '\"' && str[len - 1] == '\"')
    {
        ft_memcpy(result, str + 1, len - 2); // Copy the string without the quotes
        result[len - 2] = '\0';
        token->is_single_quoted = 0;
    }
    else 
    {
        ft_strcpy(result, str);
        token->is_single_quoted = 0;
    }
    free(token->token);
    token->token = result;
}

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

void	parse_value(t_token *token_lst, t_shell *minishell)
{
	t_token	*curr;
	char	*token;
	char	*exit_status_str;
    char    *new_token;
	int		exit_status;

	curr = token_lst;
	token = curr->token;
	exit_status = 0;
	new_token = NULL;
	if (token == NULL || token[0] != '$')
		return ;
	if (ft_strcmp(token, "$") == 0)
		return ;
	else if (ft_strcmp(token, "$?") == 0)
	{
		exit_status = minishell->last_return ;
		exit_status_str = ft_itoa(exit_status);
		free(curr->token);
		curr->token = new_token;
	}
	else if (ft_strncmp(token, "$?", 2) == 0)
	{
		exit_status = minishell->last_return ;
		exit_status_str = ft_itoa(exit_status);
        new_token = ft_strjoin(exit_status_str, token + 2);
		free(curr->token);
		curr->token = new_token;
        free(exit_status_str);
	}
	else
		handle_env_variable(curr, minishell);
}
