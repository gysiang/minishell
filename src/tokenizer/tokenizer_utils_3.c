/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:16:40 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/23 02:08:53 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_remaining_text(char **line, t_token **token_lst)
{
	char	*start;
	char	*text;

	while (ft_iswhitespace(*line))
		(*line)++;
	if (**line != '\0')
	{
		start = *line;
		while (**line && !ft_iswhitespace(*line))
			(*line)++;
		text = ft_strndup(start, *line - start);
		token_add_back(token_lst, text, T_IDENTIFIER);
		free(text);
	}
}

static void	handle_quoted_escape(char **line, t_token **token_lst)
{
	char	*start;
	int		length;
	char	*escaped_token;

	start = *line;
	(*line)++;
	while (**line && !ft_iswhitespace(*line) && **line != '|' && **line != '<'
		&& **line != '>')
		(*line)++;
	length = *line - start;
	escaped_token = (char *)malloc(length + 1);
	if (escaped_token)
	{
		ft_strncpy(escaped_token, start, length);
		escaped_token[length] = '\0';
		token_add_back(token_lst, escaped_token, T_IDENTIFIER);
		free(escaped_token);
	}
}

void	handle_backslash(char **line, t_token **token_lst)
{
	char	escaped[2];

	(*line)++;
	escaped[0] = **line;
	escaped[1] = '\0';
	if (**line == '\"' || **line == '\'')
		handle_quoted_escape(line, token_lst);
	else
		token_add_back(token_lst, escaped, T_IDENTIFIER);
	(*line)++;
}
