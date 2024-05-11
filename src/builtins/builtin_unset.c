/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:39:54 by axlee             #+#    #+#             */
/*   Updated: 2024/05/12 01:14:57 by gyong-si         ###   ########.fr       */
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
	//int	i;

	//i = 1;
    if (var_name == NULL || *var_name == '\0' || ft_isdigit(*var_name))
	{
		printf("n\n");
		return (0);
	}
	/***
	i = 1;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_' )
			return (0);
		i++;
	} **/
	return (1);
}
/***
static char *join_from_index(char **cmd, int start_index)
{
	char	*joined;
	char	*temp;
	int		i;
	size_t new_len;

	joined = (char *)malloc(1);
	if (!joined)
		return NULL;
	joined[0] = '\0';
	i = start_index;
	while (cmd[i])
	{
		new_len = ft_strlen(joined) + ft_strlen(cmd[i]) + 1;
		temp = (char *)realloc(joined, new_len);
		if (!temp)
		{
			free(joined);
			return (NULL);
		}
		joined = temp;
		ft_strcat(joined, cmd[i]);
		if (cmd[i + 1])
			ft_strcat(joined, " ");
		i++;
	}
	return (joined);
} **/


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
