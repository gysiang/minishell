/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:07 by axlee             #+#    #+#             */
/*   Updated: 2024/05/17 11:26:43 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_echo(t_shell *minishell)
{
	t_token	*token;

	token = minishell->cmd_list->next;
	while (token)
	{
		if (token->token != NULL)
		{
			printf("%s", token->token);
			if (token->next)
				printf(" ");
		}
		else
		{
			printf("null");
			if (token->next)
				printf(" ");
		}
		token = token->next;
	}
}

int	minishell_echo(t_shell *minishell)
{
	t_token	*token;
	int		newline;

	if (minishell->cmd_list == NULL)
	{
		printf("\n");
		return (0);
	}
	token = minishell->cmd_list->next;
	if (token && ft_strcmp(token->token, "-n") == 0)
	{
		newline = 0;
		token = token->next;
	}
	execute_echo(minishell);
	if (newline)
		printf("\n");
	return (0);
}

// Test cases that failed
// echo "hi" | cat | cat | cat | cat | cat | cat | cat
// Output: Stuck in zombie mode
// Correct Output: hi
// echo - "" "  " hello
// Output: - hello
// Correct Output: -     hello
// echo test     \    test
// Output: test test
// Correct Output: test   test
// echo \"test
// Output: test
// Correct Output: "test
// echo "$TEST$TEST=lol$TEST"
// Output:
// Correct Output: "test
// echo "   $TEST lol $TEST"
// Output: lol
// Correct Output:     lol
// echo $TEST$TEST=lol$TEST""lol
// Output:
// Correct Output: =lollol
// echo test "" test "" test
// Output: test test test
// Correct Output: test  test test
// echo "\$TEST"
// Output: \$TEST
// Correct Output: $TEST
// echo "$=TEST"
// Output:
// Correct Output: $=TEST
// echo "$"
// Output:
// Correct Output: $
// echo "$?TEST"
// Output:
// Correct Output: 0TEST
// echo "$1TEST"
// Output:
// Correct Output: TEST
// echo '' test
// Output: test
// Correct Output:  test