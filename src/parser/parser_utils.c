/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:33:08 by axlee             #+#    #+#             */
/*   Updated: 2024/06/27 22:21:56 by gyong-si         ###   ########.fr       */
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

int	handle_unclosed_quote(t_token *curr, t_shell *minishell, char **command)
{
	char	*delimiter;

	delimiter = "\"";
	if (here_doc(curr, minishell, delimiter, 2) == -1)
	{
		ft_putstr_fd("Error in here_doc\n", STDERR_FILENO);
		free(*command);
		return (-1);
	}
	minishell->inside_quote = 0;
	return (0);
}

void	process_input(t_token *curr, char **command, char *input,
		t_shell *minishell)
{
	int	len;
	int	i;

	len = ft_strlen(input);
	i = 0;
	while (i < len || minishell->inside_quote)
	{
		if (i < len)
		{
			handle_character(command, input, &minishell->inside_quote, i);
		}
		if (minishell->inside_quote && i == len - 1)
		{
			if (handle_unclosed_quote(curr, minishell, command) == -1)
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

	command = ft_strdup("");
	minishell->inside_quote = 0;
	minishell->flag = 0;
	process_input(token, &command, token->token, minishell);
	finalize_command(token, command);
}

/*static void	parse_unclosed(t_token *token, t_shell *minishell)
{
	char	*input;
	char	*command;
	int		inside_quote;
	int		len;
	int		i;
	char	*trimmed_command;
	char 	*delimiter;

	i = 0;
	input = token->token;
	len = ft_strlen(input);
	command = ft_strdup("");
	inside_quote = 0;
	minishell->flag = 0;
	while (i < len || inside_quote)
	{
		if (i < len)
		{
			if (input[i] == '"')
			{
				inside_quote = !inside_quote;
				command = ft_realloc(command, ft_strlen(command) + 2);
				ft_strncat(command, &input[i], 1);
			}
		}
		if (inside_quote && i == len - 1)
		{
			delimiter = "\"";
			if (here_doc(minishell, delimiter, 2) == -1)
			{
				fprintf(stderr, "Error in here_doc\n");
				free(command);
				return ;
			}
			inside_quote = 0;
		}
		i++;
	}
	trimmed_command = ft_strtrim(command, "\"");
	free(command);
	free(token->token);
	token->token = ft_strdup(trimmed_command);
	free(trimmed_command);
}*/
