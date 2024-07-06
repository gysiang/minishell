/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:12:11 by axlee             #+#    #+#             */
/*   Updated: 2024/07/06 22:07:00 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_unclosed_quote_to_token_list(char *start, char **line,
		t_token **token_lst)
{
	int		len;
	char	*unclosed_quote;

	len = *line - start;
	unclosed_quote = (char *)malloc(len + 1);
	if (unclosed_quote)
	{
		ft_strncpy(unclosed_quote, start, len);
		unclosed_quote[len] = '\0';
		token_add_back(token_lst, unclosed_quote, T_IDENTIFIER, 0);
		free(unclosed_quote);
	}
}

void	add_literal_quote_to_token_list(char quote_type, t_token **token_lst)
{
	char	*literal_quote;

	literal_quote = (char *)malloc(2);
	if (literal_quote)
	{
		literal_quote[0] = quote_type;
		literal_quote[1] = '\0';
		token_add_back(token_lst, literal_quote, T_IDENTIFIER, 0);
		free(literal_quote);
	}
}

void	handle_quotes(char **line, t_token **token_lst)
{
	char	quote_type;
	char	*start;
	int		len;

	len = ft_strlen(*line);
	quote_type = **line;
	start = *line;
	(*line)++;
	while (**line && **line != quote_type)
		(*line)++;
	if (**line == quote_type)
	{
		(*line)++;
		add_quoted_content_to_token_list(start, line, token_lst);
	}
	else if (*line[0] != *line[len - 1])
	{
		add_unclosed_quote_to_token_list(start, line, token_lst);
	}
	else
		add_literal_quote_to_token_list(quote_type, token_lst);
}

static void	process_line(char **line, t_token **token_lst, t_shell *minishell)
{
	(void)minishell;
	if (ft_iswhitespace(*line))
		(*line)++;
	else if (**line == '\\')
		handle_backslash(line, token_lst);
	else if (**line == '$')
		handle_environment_variable(line, token_lst, minishell);
	else if (**line == '\"' || **line == '\'')
		handle_quotes(line, token_lst);
	else if (ft_strncmp(*line, "|", 1) == 0)
		add_symbol_lst(line, T_PIPE, token_lst);
	else if (ft_strncmp(*line, "<<", 2) == 0)
		add_symbol_lst(line, T_LEFT_SHIFT, token_lst);
	else if (ft_strncmp(*line, ">>", 2) == 0)
		add_symbol_lst(line, T_RIGHT_SHIFT, token_lst);
	else if (ft_strncmp(*line, "<", 1) == 0)
		add_symbol_lst(line, T_LESSER_THAN, token_lst);
	else if (ft_strncmp(*line, ">", 1) == 0)
		add_symbol_lst(line, T_GREATER_THAN, token_lst);
	else
	{
		add_command_lst(line, token_lst);
		while (ft_iswhitespace(*line))
			(*line)++;
	}
}

t_token	*token_processor(char *line, t_shell *minishell)
{
	t_token	*token_lst;

	(void)minishell;
	token_lst = NULL;
	while (*line != '\0')
		process_line(&line, &token_lst, minishell);
	token_lst = token_parser(token_lst, minishell);
	return (token_lst);
}
