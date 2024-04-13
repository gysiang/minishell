/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:13:16 by axlee             #+#    #+#             */
/*   Updated: 2024/04/12 12:25:43 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_pwd(t_shell *minishell, t_cmd *cmd)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("Error retrieving current directory");
		cmd->return_value = 1;
	}
	else
	{
		printf("%s\n", pwd);
		cmd->return_value = 0;
	}
	return (cmd->return_value);
}
