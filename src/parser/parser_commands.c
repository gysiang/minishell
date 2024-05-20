/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:54:35 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/20 13:18:19 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_singlequote(t_token *t)
{
	char	*result;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = t->token;
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return ;
	while (str[i] != '\0')
	{
		if (str[i] != '\'')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	free(t->token);
	t->token = result;
	return ;
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
		free(curr->token);
		curr->token = exit_status_str;
	}
	else
		handle_env_variable(curr, minishell);
}

void	parse_doublequote(t_token *t)
{
	char	*result;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = t->token;
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return ;
	while (str[i] != '\0')
	{
		if (str[i] != '\"')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	free(t->token);
	t->token = result;
	return ;
}
