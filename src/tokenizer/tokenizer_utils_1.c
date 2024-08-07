/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:13:57 by axlee             #+#    #+#             */
/*   Updated: 2024/07/06 22:39:33 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_wordlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s != c && *s != '|')
	{
		i++;
		s++;
	}
	return (i);
}

int	add_symbol_lst(char **line, t_token_type type, t_token **token_lst)
{
	int		word_len;
	char	*symbol;

	if (type == T_LEFT_SHIFT || type == T_RIGHT_SHIFT)
		word_len = 2;
	else
		word_len = 1;
	symbol = (char *)malloc(word_len + 1);
	if (!symbol)
		return (0);
	ft_copy(symbol, *line, word_len);
	symbol[word_len] = '\0';
	token_add_back(token_lst, symbol, type, 0);
	free(symbol);
	(*line) += word_len;
	return (0);
}

static void	skip_whitespace_and_extract_command(char **line, char **start)
{
	while (ft_iswhitespace(*line))
		(*line)++;
	*start = *line;
	while (**line && !ft_iswhitespace(*line) && **line != '|' && **line != '<'
		&& **line != '>' && **line != '\'' && **line != '\"' && **line != '$')
		(*line)++;
}

static void	skip_quotes(char **line)
{
	char	quote_type;

	quote_type = **line;
	(*line)++;
	while (**line && **line != quote_type)
		(*line)++;
	if (**line == quote_type)
		(*line)++;
}

int	add_command_lst(char **line, t_token **token_lst)
{
	char	*start;
	char	*cmd;
	int		i;

	i = 0;
	if (**line == '\"' || **line == '\'')
		skip_quotes(line);
	skip_whitespace_and_extract_command(line, &start);
	if (*line != start)
	{
		cmd = ft_strndup(start, *line - start);
		if (ft_iswhitespace(*line++))
			i = 1;
		token_add_back(token_lst, cmd, T_IDENTIFIER, i);
		free(cmd);
	}
	return (0);
}
