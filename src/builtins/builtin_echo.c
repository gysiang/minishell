/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:07 by axlee             #+#    #+#             */
/*   Updated: 2024/06/06 19:16:09 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_tokens(t_token *current_token, t_shell *minishell, int newline)
{
    while (current_token != NULL)
    {
        if (current_token->type == T_IDENTIFIER)
        {
            parse_token(current_token, minishell); // Parse the token
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

void minishell_echo(t_shell *minishell)
{
    int newline;
    t_token *current_token;

    newline = 1;  // Default is to print newline at the end
    if (minishell->cmd_list == NULL)
        return;
    current_token = minishell->cmd_list->next; // Skip the 'echo' command itself
    // Check for '-n' option which suppresses the newline
    if (current_token != NULL && strcmp(current_token->token, "-n") == 0) {
        newline = 0;  // Do not print newline at the end
        current_token = current_token->next;  // Move to the next token
    }
    print_tokens(current_token, minishell, newline);
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
