/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:16:40 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/06 10:01:02 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_wordlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	return (i);
}

int add_symbol_lst(char **line, t_token_type type, t_token **token_lst)
{
    int word_len;
    char *symbol;

    word_len = ft_wordlen(*line, ' ');
    symbol = (char *)malloc(word_len + 1);
    if (!symbol)
        return (0);
    ft_copy(symbol, *line, word_len);
    token_add_back(token_lst, symbol, type);
    free(symbol);
    if (type == T_LEFT_SHIFT || type == T_RIGHT_SHIFT)
        (*line) += 2;
    else
        (*line)++;
    return (0);
}

int add_command_lst(char **line, t_token **token_lst)
{
    int word_len;
    char *cmd;

    word_len = ft_wordlen(*line, ' ');
    cmd = (char *)malloc(word_len + 1);
    if (!cmd)
        return (0);
    ft_copy(cmd, *line, word_len);
    token_add_back(token_lst, cmd, T_IDENTIFIER);
    free(cmd);
    (*line) += word_len;
    return (0);
}

t_token	*token_processor(char *line, t_shell *minishell)
{
	t_token	*token_lst;

	token_lst = NULL;
	while (*line != '\0')
	{
		if (ft_iswhitespace(line) || ft_isbackslash(line))
			line++;
		else if (!ft_strncmp(line, "|", 1))
			add_symbol_lst(&line, T_PIPE, &token_lst);
		else if (!ft_strncmp(line, "<<", 2))
			add_symbol_lst(&line, T_LEFT_SHIFT, &token_lst);
		else if (!ft_strncmp(line, "<", 1))
			add_symbol_lst(&line, T_LESSER_THAN, &token_lst);
		else if (!ft_strncmp(line, ">>", 2))
			add_symbol_lst(&line, T_RIGHT_SHIFT, &token_lst);
		else if (!ft_strncmp(line, ">", 1))
			add_symbol_lst(&line, T_GREATER_THAN, &token_lst);
		else
			add_command_lst(&line, &token_lst);
	}
	token_lst = token_parser(token_lst, minishell);
	return (token_lst);
}
