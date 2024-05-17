/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:39:54 by axlee             #+#    #+#             */
/*   Updated: 2024/05/12 01:42:10 by gyong-si         ###   ########.fr       */
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

int	minishell_unset(t_shell *minishell)
{
	int	var_index;
	t_token *token;
	char	**cmd;
	int	i;

	i = 1;
	token = minishell->cmd_list;
	cmd = ft_split(token->token, ' ');
	while (cmd[i])
	{
		if (!is_valid_var_name(cmd[i]))
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
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
	return (0);
}
