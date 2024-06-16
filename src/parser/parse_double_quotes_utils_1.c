/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_quotes_utils_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:16:55 by axlee             #+#    #+#             */
/*   Updated: 2024/06/16 22:11:23 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prepend_dollar(const char *var_name)
{
	char	*result;
	size_t	len;

	len = ft_strlen(var_name);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	result[0] = '$';
	ft_strcpy(result + 1, var_name);
	return (result);
}

void	append_to_result(char **result, t_shell *minishell, const char *str)
{
	size_t	str_len;
	size_t	new_size;
	char	*new_result;

	str_len = ft_strlen(str);
	if (minishell->j + str_len + 1 > minishell->allocated_size)
	{
		new_size = minishell->j + str_len + 1;
		new_result = malloc(new_size);
		if (new_result == NULL)
		{
			free(*result);
			*result = NULL;
			return ;
		}
		ft_memcpy(new_result, *result, minishell->j);
		free(*result);
		*result = new_result;
		minishell->allocated_size = new_size;
	}
	ft_strcpy(&(*result)[minishell->j], str);
	minishell->j += str_len;
}

/*void	append_to_result(char **result, t_shell *minishell, const char *str)
{
	size_t	str_len;

	str_len = ft_strlen(str);
	if (minishell->j + str_len + 1 > minishell->allocated_size)
	{
		minishell->allocated_size = minishell->j + str_len + 1;
		*result = ft_realloc(*result, minishell->allocated_size);
	}
	ft_strcpy(&(*result)[minishell->j], str);
	minishell->j += str_len;
}*/
void	handle_variable_value(char **result, t_shell *minishell,
		char *var_value)
{
	if (var_value)
	{
		append_to_result(result, minishell, var_value);
		// minishell->flag = 1;
		free(var_value);
	}
}

void	handle_variable_not_found(char **result, t_shell *minishell,
		const char *var_name)
{
	(void)var_name;
	append_to_result(result, minishell, "");
}

/*void	handle_variable_not_found(char **result, t_shell *minishell,
		const char *var_name)
{
	char	*temp;

	temp = prepend_dollar(var_name);
	append_to_result(result, minishell, temp);
	free(temp);
}*/

/*void	handle_env_variable_expansion(char *str, char **result,
		t_shell *minishell)
{
	char	var_name[256];
	char	*var_value;
	int		var_len;
	char	var_name[256];
	char	*var_value;
	int		var_len;

	var_len = 0;
	minishell->i++;
	while (ft_isalnum(str[minishell->i]) || str[minishell->i] == '_')
		var_name[var_len++] = str[minishell->i++];
	var_name[var_len] = '\0';
	var_value = get_env_value(minishell, var_name);
	if (var_value)
		handle_variable_value(result, minishell, var_value);
	else
		handle_variable_not_found(result, minishell, var_name);
}*/
