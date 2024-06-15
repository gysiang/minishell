/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:16:05 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/15 13:03:37 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_and_free(char *s1, const char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

static char	*replace_env_value(char *start, char *end, t_shell *minishell)
{
	char	*var_name;
	char	*env_value;

	var_name = ft_substr(start, 1, end - start - 1);
	env_value = get_env_value(minishell, var_name);
	free(var_name);
	if (!env_value)
		env_value = ft_strdup("");
	return (env_value);
}

char	*expand_env_variable(char *str, t_shell *minishell)
{
	char	*start;
	char	*end;
	char	*env_value;
	char	*result;
	size_t	len;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (ft_strchr(str, '$'))
	{
		start = ft_strchr(str, '$');
		len = start - str;
		result = join_and_free(result, ft_substr(str, 0, len));
		end = start + 1;
		while (ft_isalnum(*end) || *end == '_')
			end++;
		env_value = replace_env_value(start, end, minishell);
		result = join_and_free(result, env_value);
		free(env_value);
		str = end;
	}
	result = join_and_free(result, ft_strdup(str));
	return (result);
}

int	read_input(char **str, char *delimiter, int i, t_shell *minishell)
{
	*str = readline("> ");
	if (!*str)
	{
		if (i == 1)
			printf("End of file reached\n");
		minishell->signal_received = 1;
		error_eof(delimiter, i);
		return (0);
	}
	return (1);
}

int	is_delimiter(const char *str, const char *delimiter)
{
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	return (!ft_strncmp(str, delimiter, delimiter_len + 1));
}
