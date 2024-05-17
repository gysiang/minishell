/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:39:54 by axlee             #+#    #+#             */
/*   Updated: 2024/05/17 13:11:15 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shift_env_entries(t_shell *minishell, int start_index)
{
	while (minishell->env[start_index + 1])
	{
		minishell->env[start_index] = minishell->env[start_index + 1];
		start_index++;
	}
	minishell->env[start_index] = NULL;
}

int	search_env(t_shell *minishell, char *var)
{
	int	i;

	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	is_valid_var_name(char *var_name)
{
	if (var_name == NULL || *var_name == '\0' || ft_isdigit(*var_name))
	{
		printf("n\n");
		return (0);
	}
	return (1);
}

static int	not_valid_var(char **cmd, int index)
{
	if (!is_valid_var_name(cmd[index]))
	{
		printf("minishell: unset: '%s': not a valid identifier\n", cmd[index]);
		return (1);
	}
	return (0);
}

int	minishell_unset(t_shell *minishell)
{
	int		var_index;
	t_token	*token;
	char	**cmd;
	int		i;

	i = 1;
	token = minishell->cmd_list;
	cmd = ft_split(token->token, ' ');
	while (cmd[i])
	{
		if (not_valid_var(cmd, i) == 0)
		{
			var_index = search_env(minishell, cmd[i]);
			if (var_index >= 0)
			{
				shift_env_entries(minishell, var_index);
				printf("removed env index %d\n", var_index);
			}
		}
		i++;
	}
	ft_split_free(&cmd);
	return (0);
}
