/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:13:57 by axlee             #+#    #+#             */
/*   Updated: 2024/07/06 12:45:07 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokenlst(t_token *token_lst)
{
	t_token	*curr;

	curr = token_lst;
	while (curr != NULL)
	{
		printf("token: %s\n", curr->token);
		printf("token type: %d\n", curr->type);
		printf("token space: %d\n", curr->space);
		curr = curr->next;
	}
}

static char	*append_char_to_result(char *result, char c)
{
	size_t	current_length;
	size_t	new_size;
	char	*new_result;

	current_length = ft_strlen(result);
	new_size = current_length + 2;
	new_result = malloc(new_size);
	if (new_result == NULL)
	{
		free(result);
		return (NULL);
	}
	ft_memcpy(new_result, result, current_length);
	new_result[current_length] = c;
	new_result[current_length + 1] = '\0';
	free(result);
	return (new_result);
}

void	append_rest_of_line(char **line, char *result, t_token **token_lst)
{
	char	i;

	i = 0;
	if (**line && !ft_iswhitespace(*line) && **line != '$' && **line != '\''
		&& **line != '\"')
	{
		result = append_char_to_result(result, **line);
		if (result == NULL)
			return ;
		(*line)++;
		if (ft_iswhitespace(*line))
			i = 1;
	}
	token_add_back(token_lst, result, T_IDENTIFIER, i);
	free(result);
}

void	handle_special_case(char **line, t_token **token_lst,
		t_shell *minishell)
{
	char	*expanded;
	int		var_len;
	char	*result;

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
