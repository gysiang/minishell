/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:45:07 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/17 16:01:27 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(char *cmd)
{
	char	*equal_pos;

	equal_pos = ft_strchr(cmd, '=');
	if (equal_pos)
		return (ft_substr(cmd, 0, equal_pos - cmd));
	return (NULL);
}

static int	is_valid_identifier(const char *str)
{
	if (str == NULL || *str == '\0' || ft_isdigit(*str))
		return (0);
	return (1);
}

static int	save_var(t_shell *minishell, char *content)
{
	char	*var_name;
	int		var_index;

	printf("inside savevar\n");
	if (!is_valid_identifier(content))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(content, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	var_name = get_var_name(content);
	if (!var_name)
		return (0);
	var_index = search_env(minishell, var_name);
	if (var_index == -1)
		var_index = env_len(minishell);
	if (var_index == minishell->env_size)
	{
		printf("Environment size reached. Reallocating...\n");
		env_realloc(minishell);
	}
	minishell->env[var_index] = ft_strdup(content);
	return (0);
}

int	minishell_export(t_shell *minishell)
{
	t_token	*token;
	char	**cmd;
	char	*joined;

	token = minishell->cmd_list;
	if (!token)
	{
		print_vars(minishell);
		return (0);
	}
	cmd = ft_split(token->token, ' ');
	joined = join_from_index(cmd, 1);
	if (joined)
	{
		save_var(minishell, joined);
	}
	free(joined);
	return (0);
}
