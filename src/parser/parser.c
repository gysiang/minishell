/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:54:35 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/10 15:29:17 by gyong-si         ###   ########.fr       */
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
	char	*exit_status_str;
	int		exit_status;

	curr = token_lst;
	token = curr->token;
	exit_status = 0;
	if (token == NULL || token[0] != '$')
		return ;
	if (ft_strcmp(token, "$")== 0)
		return ;
	else if (ft_strcmp(token, "$?") == 0)
	{
		exit_status = minishell->last_return;
		exit_status_str = ft_itoa(exit_status);
		free(curr->token);
		curr->token = exit_status_str;
	}
	else
	{
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


static void set_token_pointers(t_token *tokens)
{
    t_token *prev_token = NULL;
    t_token *curr_token = tokens;

    while (curr_token != NULL)
    {
        curr_token->prev = prev_token;
        if (prev_token != NULL)
            prev_token->next = curr_token;
        prev_token = curr_token;
        curr_token = curr_token->next;
    }
    if (prev_token != NULL)
        prev_token->next = NULL;
}


static void handle_cd_command(t_token **curr, t_shell *minishell)
{
    t_token *next_token = (*curr)->next;
    if (next_token != NULL && next_token->type == T_IDENTIFIER)
    {
        char *dir = next_token->token;
        if (chdir(dir) != 0)
        {
            perror("minishell: cd");
            minishell->last_return = 1;
        }
        else
            minishell->last_return = 0;
        *curr = next_token->next; // Move to the token after the directory argument
    }
    else
    {
        fprintf(stderr, "minishell: cd: too few arguments\n");
        minishell->last_return = 1;
        *curr = (*curr)->next; // Move to the next token
    }
}

t_token *token_parser(t_token *token_lst, t_shell *minishell)
{
    t_token *curr = token_lst;
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
        else if (ft_strcmp(curr->token, "cd") == 0)
		{
            handle_cd_command(&curr, minishell);
            continue;
        }
        curr = curr->next;
    }
    join_identifier_tokens(token_lst);
    set_token_pointers(token_lst);
    return token_lst;
}