/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/11 00:43:07 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt()
{
	printf("minishell$ ");
	fflush(stdout);
	usleep(500000);
	printf("\b ");
	fflush(stdout);
	usleep(500000);
}

int	main()
{
	char	command[100];

	while (1)
	{
		prompt();
		if (fgets(command, sizeof(command), stdin) == NULL)
			break ;
	}
	return (0);
}
