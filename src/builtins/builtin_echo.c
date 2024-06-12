/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:07 by axlee             #+#    #+#             */
/*   Updated: 2024/06/12 10:32:42 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tokens(t_token *current, t_shell *minishell, int newline)
{
	while (current != NULL)
	{
		if (current->type == T_IDENTIFIER)
		{
			parse_token(current, minishell);
			printf("%s", current->token);
			if (current->next && current->next->token[0] != '\0')
			{
				if (current->token[ft_strlen(current->token) - 1] != '\0')
					printf(" ");
			}
		}
		else
			break ;
		current = current->next;
	}
	if (newline)
		printf("\n");
}

/*static void	print_tokens(t_token *current, t_shell *minishell, int newline)
{
	while (current != NULL)
	{
		if (current->type == T_IDENTIFIER)
		{
			parse_token(current, minishell);
			printf("%s", current->token);
			if (current->next && current->next->token[0] != '\0')
			{
				if (current->token[ft_strlen(current->token) - 1] != '\0')
					printf(" ");
			}
		}
		else
			break ;
		current = current->next;
	}
	if (newline)
		printf("\n");
}*/

void	minishell_echo(t_shell *minishell)
{
	int		newline;
	t_token	*current;

	newline = 1;
	if (minishell->cmd_list == NULL)
		return ;
	current = minishell->cmd_list->next;
	if (current != NULL && strcmp(current->token, "-n") == 0)
	{
		newline = 0;
		current = current->next;
	}
	print_tokens(current, minishell, newline);
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
// echo "$="
// Output:
// Correct Output: $=
// echo "$?"
// Output:
// Correct Output: 0TEST
// echo "$1TEST"
// Output:
// Correct Output: TEST
// echo '' test
// Output: test
// Correct Output:  test
