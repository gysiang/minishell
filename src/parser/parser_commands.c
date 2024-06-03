/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:54:35 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/04 02:42:01 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void parse_singlequote(t_token *t)
{
    char *result;
    char *str;
    int i;
    int j;

    i = 0;
    j = 0;
    str = t->token;
    result = (char *)malloc(strlen(str) + 1);
    if (!result)
        return;

    while (str[i] != '\0') {
        if (str[i] == '\'') {
            i++;  // Skip the opening single quote
            while (str[i] != '\'' && str[i] != '\0') {
                result[j++] = str[i++];  // Copy everything inside the single quotes
            }
            if (str[i] == '\'') {
                i++;  // Skip the closing single quote
            }
        } else {
            result[j++] = str[i++];
        }
    }
    result[j] = '\0';
    free(t->token);
    t->token = result;
}*/


/*void parse_doublequote(t_token *t)
{
    char *result;
    char *str;
    int i;
    int j;

    i = 0;
    j = 0;
    str = t->token;
    result = (char *)malloc(strlen(str) + 1);
    if (!result)
        return;

    while (str[i] != '\0') {
        if (str[i] == '\"') {
            i++;  // Skip the opening single quote
            while (str[i] != '\"' && str[i] != '\0') {
                result[j++] = str[i++];  // Copy everything inside the single quotes
            }
            if (str[i] == '\"') {
                i++;  // Skip the closing single quote
            }
        } else {
            result[j++] = str[i++];
        }
    }
    result[j] = '\0';
    free(t->token);
    t->token = result;
}*/

void parse_quotes(t_token *token)
{
    char *str = token->token;
    int len = strlen(str);
    char *result = malloc(len + 1); // Allocate space for the new string
    if (!result) return; // Always check malloc return

    // Check if the entire token is encapsulated by single or double quotes
    if (len > 1 && ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"' && str[len - 1] == '\"'))) {
        // Copy the inside, excluding the outermost quotes
        memcpy(result, str + 1, len - 2);
        result[len - 2] = '\0'; // Null-terminate the new string
    } else {
        // If not encapsulated by quotes, just copy the string
        strcpy(result, str);
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
		env_value = (" ");
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
	if (token == NULL || token[0] != '$')
		return ;
	if (ft_strcmp(token, "$") == 0)
		return ;
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

