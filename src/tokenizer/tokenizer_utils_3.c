/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:11:15 by axlee             #+#    #+#             */
/*   Updated: 2024/06/26 13:26:45 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*allocate_and_copy_result(const char *source)
{
	char	*result;

	result = malloc(ft_strlen(source) + 1);
	if (result)
	{
		ft_strcpy(result, source);
	}
	return (result);
}

void	handle_expansion(char **line, char *expanded, t_token **token_lst)
{
	char	*result;

	result = allocate_and_copy_result(expanded);
	if (result)
	{
		free(expanded);
		append_rest_of_line(line, result, token_lst);
	}
}

void	handle_variable_expansion(char **line, char *start, t_token **token_lst,
		t_shell *minishell)
{
	char	*var_name;
	char	*expanded;
	char	*result;
	int		var_len;

	var_len = *line - start;
	var_name = ft_strndup(start, var_len);
	if (var_len == 1 && var_name[0] == '$')
	{
		result = ft_strdup("$");
		token_add_back(token_lst, result, T_IDENTIFIER);
		free(result);
		free(var_name);
		return ;
	}
	expanded = get_env_value(minishell, var_name, 1);
	free(var_name);
	if (expanded)
		handle_expansion(line, expanded, token_lst);
	else
	{
		result = ft_strndup(start - 1, var_len + 1);
		token_add_back(token_lst, result, T_IDENTIFIER);
		free(result);
	}
}

void    handle_environment_variable(char **line, t_token **token_lst,
        t_shell *minishell)
{
    char    *start;
    char    *var_name;
    char    *var_value;

    start = *line;
    (*line)++;
    if (**line == '?')
    {
        handle_special_case(line, token_lst, minishell);
        return ;
    }
    while (**line && (ft_isalnum(**line) || **line == '_'))
        (*line)++;
    var_name = ft_strndup(start + 1, *line - start - 1);
    if (!var_name)
        return ;
    var_value = get_env_value(minishell, var_name, 1);
    free(var_name);
    if (!var_value)
        var_value = ft_strdup("");
    if (var_value)
    {
        token_add_back(token_lst, var_value, T_IDENTIFIER);
        free(var_value);
    }
}

/*void	handle_environment_variable(char **line, t_token **token_lst,
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
}*/
