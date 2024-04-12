/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/11 21:09:27 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main()
{
	char	*input;

	using_history();
	setup_signal_handler();
	while (1)
	{
		prompt();
		input = readline(" ");
		if (input == NULL)
		{
			printf("exit\n");
			break;
		}
		if (*input == '\0')
		{
			free(input);
			continue;
		}
		printf("This is user input: %s\n", input);
		hist_feature(input);
		free(input);
	}
	return (0);
}
