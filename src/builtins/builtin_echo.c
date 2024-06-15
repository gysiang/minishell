/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:07 by axlee             #+#    #+#             */
/*   Updated: 2024/06/15 13:27:57 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_input_fd(t_shell *minishell)
{
	char buffer[1024];
	ssize_t bytes_read;

	printf("\n");
	while ((bytes_read = read(minishell->input_fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		printf("%s", buffer);
	}
}

static void	print_tokens(t_token *current, t_shell *minishell, int newline)
{
	int first;

	first = 1;
	while (current != NULL)
	{
		if (current->type == T_IDENTIFIER && ft_strcmp(current->token, "") != 0)
		{
			if (current->prev && current->prev->type == T_IDENTIFIER
				&& ft_strcmp(current->prev->token, "") == 0)
				first = 1;
			if (!first)
				printf(" ");
			printf("%s", current->token);
			first = 0;
		}
		else if (current->type == T_IDENTIFIER && !ft_strcmp(current->token, ""))
		{
			current = current->next;
			continue;
		}
		else
			break;
		current = current->next;
	}
	if (minishell->flag)
	{
		print_input_fd(minishell);
		close(minishell->input_fd);
	}
	if (newline)
		printf("\n");
}

/*static void	print_tokens(t_token *current, t_shell *minishell, int newline)
{
	(void)minishell;

	while (current != NULL)
	{
		if (current->type == T_IDENTIFIER)
		{
			//parse_token(current, minishell);
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
	if (minishell->flag)
	{
		print_input_fd(minishell);
		close(minishell->input_fd);
	}
	if (newline)
		printf("\n");
}*/

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
	if (minishell->signal_received)
		exit(1);
	current = minishell->cmd_list->next;
	if (current != NULL && ft_strcmp(current->token, "-n") == 0)
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
