/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:12:11 by axlee             #+#    #+#             */
/*   Updated: 2024/06/10 20:42:04 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(char **line, t_token **token_lst)
{
	char	quote_type;
	char	*start;
	int		length;
	char	*quoted_content;
	char	*literal_quote;

	quote_type = **line;
	start = *line;
	(*line)++;
	while (**line && **line != quote_type)
		(*line)++;
	if (**line == quote_type)
	{
		(*line)++;
		length = *line - start;
		quoted_content = (char *)malloc(length + 1);
		if (quoted_content)
		{
			ft_strncpy(quoted_content, start, length);
			quoted_content[length] = '\0';
			token_add_back(token_lst, quoted_content, T_IDENTIFIER);
			free(quoted_content);
		}
	}
	else
	{
		literal_quote = (char *)malloc(2);
		if (literal_quote)
		{
			literal_quote[0] = quote_type;
			literal_quote[1] = '\0';
			token_add_back(token_lst, literal_quote, T_IDENTIFIER);
			free(literal_quote);
		}
	}
}

t_token	*token_processor(char *line, t_shell *minishell)
{
	t_token	*token_lst;

	(void)minishell;
	token_lst = NULL;
	while (*line != '\0')
	{
		if (ft_iswhitespace(line))
			line++;
		else if (*line == '\\')
			handle_backslash(&line, &token_lst);
		else if (*line == '$')
			handle_environment_variable(&line, &token_lst, minishell);
		else if (*line == '\"' || *line == '\'')
			handle_quotes(&line, &token_lst);
		else if (ft_strncmp(line, "|", 1) == 0)
			add_symbol_lst(&line, T_PIPE, &token_lst);
		else if (ft_strncmp(line, "<<", 2) == 0)
			add_symbol_lst(&line, T_LEFT_SHIFT, &token_lst);
		else if (ft_strncmp(line, ">>", 2) == 0)
			add_symbol_lst(&line, T_RIGHT_SHIFT, &token_lst);
		else if (ft_strncmp(line, "<", 1) == 0)
			add_symbol_lst(&line, T_LESSER_THAN, &token_lst);
		else if (ft_strncmp(line, ">", 1) == 0)
			add_symbol_lst(&line, T_GREATER_THAN, &token_lst);
		else
		{
			add_command_lst(&line, &token_lst);
			while (ft_iswhitespace(line))
				line++;
		}
	}
	token_lst = token_parser(token_lst, minishell);
	return (token_lst);
}
