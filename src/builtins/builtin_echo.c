/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:07 by axlee             #+#    #+#             */
/*   Updated: 2024/06/02 12:57:26 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell_echo(t_shell *minishell)
{
	printf("inside minishell echo\n");
    int newline = 1;  // Default is to print newline at the end

    if (minishell->cmd_list == NULL)
        return;

    t_token *current_token = minishell->cmd_list->next; // Skip the 'echo' command itself

    // Check for '-n' option which suppresses the newline
    if (current_token != NULL && strcmp(current_token->token, "-n") == 0) {
        newline = 0;  // Do not print newline at the end
        current_token = current_token->next;  // Move to the next token
    }

    while (current_token != NULL)
    {
        if (current_token->type == T_IDENTIFIER)
        {
            parse_quotes(current_token); // Parse quotes for each token
            printf("%s", current_token->token);
            if (current_token->next)
                printf(" ");  // Add space between arguments
        }
        else
            break;
        current_token = current_token->next;
    }
    if (newline)
        printf("\n");
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
