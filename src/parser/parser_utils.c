/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:33:08 by axlee             #+#    #+#             */
/*   Updated: 2024/07/04 00:24:26 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_character(char **command, char *input, int *inside_quote, int i)
{
	if (input[i] == '"')
	{
		*inside_quote = !(*inside_quote);
	}
	*command = ft_realloc(*command, ft_strlen(*command) + 2);
	ft_strncat(*command, &input[i], 1);
}

int	handle_unclosed_quote(t_shell *minishell, char **command, int *inside_quote)
{
	char	*delimiter;

	delimiter = "\"";
	if (here_doc(minishell, delimiter, 2) == -1)
	{
		ft_putstr_fd("Error in here_doc\n", STDERR_FILENO);
		free(*command);
		return (-1);
	}
	*inside_quote = 0;
	return (0);
}

void	process_input(char **command, char *input, int *inside_quote,
		t_shell *minishell)
{
	int	len;
	int	i;

	len = ft_strlen(input);
	i = 0;
	while (i < len || *inside_quote)
	{
		if (i < len)
		{
			handle_character(command, input, inside_quote, i);
		}
		if (*inside_quote && i == len - 1)
		{
			if (handle_unclosed_quote(minishell, command, inside_quote) == -1)
				return ;
		}
		i++;
	}
}

void	finalize_command(t_token *token, char *command)
{
	char	*trimmed_command;

	trimmed_command = ft_strtrim(command, "\"");
	free(command);
	free(token->token);
	token->token = ft_strdup(trimmed_command);
	free(trimmed_command);
}

void	parse_unclosed(t_token *token, t_shell *minishell)
{
	char	*command;
	int		inside_quote;

	command = ft_strdup("");
	inside_quote = 0;
	minishell->flag = 1;
	process_input(&command, token->token, &inside_quote, minishell);
	finalize_command(token, command);
}
