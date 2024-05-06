/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:54:35 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/06 09:50:33 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_singlequote(t_token *t)
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

static void	parse_semicolon(t_token *token)
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

static void	parse_value(t_token *token_lst, t_shell *minishell)
{
	t_token	*curr;
	char	*token;
	char	*result;
	char	*env_value;

	curr = token_lst;
	token = curr->token;
	if (token == NULL || token[0] != '$')
		return ;
	result = ft_substr(token, 1, ft_strlen(token) - 1);
	if (!result)
		return ;
	env_value = get_env_value(minishell, result);
	free(result);
	if (!env_value)
		env_value = " ";
	free(curr->token);
	curr->token = env_value;
}

static void	parse_doublequote(t_token *t)
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

t_token	*token_parser(t_token *token_lst, t_shell *minishell)
{
	t_token	*curr;

	curr = token_lst;
	while (curr != NULL)
	{
		if (ft_strchr(curr->token, '\''))
			parse_singlequote(curr);
		else if (ft_strchr(curr->token, ';'))
			parse_semicolon(curr);
		else if (ft_strchr(curr->token, '$'))
		{
			parse_doublequote(curr);
			parse_value(curr, minishell);
		}
		else if (ft_strchr(curr->token, '\"'))
			parse_doublequote(curr);
		curr = curr -> next;
	}
	join_identifier_tokens(token_lst);
	return (token_lst);
}
