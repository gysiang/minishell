/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:13:57 by axlee             #+#    #+#             */
/*   Updated: 2024/06/13 12:25:38 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print the linked list that holds the tokens;
void	print_tokenlst(t_token *token_lst)
{
	t_token	*curr;

	curr = token_lst;
	while (curr != NULL)
	{
		printf("token: %s\n", curr->token);
		printf("token type: %d\n", curr->type);
		curr = curr->next;
	}
}

static void	append_rest_of_line(char **line, char *result, t_token **token_lst)
{
	size_t	current_length;

	while (**line && !ft_iswhitespace(*line) && **line != '$' && **line != '\''
		&& **line != '\"')
	{
		current_length = strlen(result);
		result = ft_realloc(result, current_length + 2);
		ft_strncat(result, *line, 1);
		(*line)++;
	}
	token_add_back(token_lst, result, T_IDENTIFIER);
	free(result);
}

static void	handle_special_case(char **line, t_token **token_lst,
		t_shell *minishell)
{
	char	*expanded;
	char	*result;
	int		var_len;

	(*line)++;
	expanded = ft_itoa(minishell->last_return);
	var_len = ft_strlen(expanded);
	result = malloc(var_len + 1);
	if (result)
	{
		ft_strcpy(result, expanded);
		free(expanded);
		append_rest_of_line(line, result, token_lst);
	}
}

static void	handle_variable_expansion(char **line, char *start,
		t_token **token_lst, t_shell *minishell)
{
	char	*var_name;
	char	*expanded;
	char	*result;
	int		var_len;

	var_len = *line - start;
	var_name = ft_strndup(start, var_len);
	expanded = get_env_value(minishell, var_name);
	free(var_name);
	if (expanded)
	{
		result = malloc(strlen(expanded) + 1);
		if (result)
		{
			ft_strcpy(result, expanded);
			free(expanded);
			append_rest_of_line(line, result, token_lst);
		}
	}
	else
	{
		result = ft_strndup(start - 1, var_len + 1);
		token_add_back(token_lst, result, T_IDENTIFIER);
		free(result);
	}
}

void	handle_environment_variable(char **line, t_token **token_lst,
		t_shell *minishell)
{
	char	*start;

	start = *line;
	(*line)++;
	start = *line;
	if (**line == '?')
	{
		handle_special_case(line, token_lst, minishell);
		return ;
	}
	while (**line && (ft_isalnum(**line) || **line == '_'))
		(*line)++;
	handle_variable_expansion(line, start, token_lst, minishell);
}
