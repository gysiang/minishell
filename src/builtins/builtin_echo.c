/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:07 by axlee             #+#    #+#             */
/*   Updated: 2024/05/04 15:36:05 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int minishell_echo(t_shell *minishell)
{
	
    t_token *token;
    int newline;

	newline = 1;
	token = minishell->cmd_list;
    token = token->next;
    if (token && ft_strcmp(token->token, "-n") == 0)
    {
        newline = 0;
        token = token->next;
    }
    while (token)
    {
        printf("%s", token->token);
        if (token->next)
            printf(" ");
    }
    if (newline)
        printf("\n");
    return (0);
}

// Test cases that failed
// echo $?
// Output:
// Correct Output: 0
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
//echo '' test  
//  test