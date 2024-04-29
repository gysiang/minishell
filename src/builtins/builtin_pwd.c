/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:13:16 by axlee             #+#    #+#             */
/*   Updated: 2024/04/29 21:42:46 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_pwd(t_shell *minishell)
{
	if (minishell->pwd == NULL)
		return (1);
	else
	{
		printf("%s\n", minishell->pwd);
		return (0);
	}
}
