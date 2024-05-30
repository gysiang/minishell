/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:31:06 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/30 19:52:59 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*concat_token(const char *token1, const char *token2)
{
	size_t	len1;
	size_t	len2;
	size_t	total_len;
	char	*joined_str;

	len1 = ft_strlen(token1);
	len2 = ft_strlen(token2);
	total_len = len1 + len2 + 2;
	joined_str = (char *)malloc(total_len);
	if (!joined_str)
		return (NULL);
	ft_copy(joined_str, token1, len1);
	ft_strcat(joined_str, " ");
	ft_strcat(joined_str, token2);
	return (joined_str);
}

static void	merge_identifier_tokens(t_token *curr)
{
	char	*joined;
	t_token	*next;

	joined = concat_token(curr->token, curr->next->token);
	if (joined)
	{
		free(curr->token);
		curr->token = joined;
		next = curr->next;
		curr->next = next->next;
		free(next);
	}
}


static bool is_command(char *token)
{
    // Implement a check to see if the token is a known command
    static const char *commands[] = {
        "cd", "ls", "echo", "exit", "unset", "pwd", "env", "export", NULL
    };
    for (int i = 0; commands[i]; i++)
    {
        if (strcmp(token, commands[i]) == 0)
            return true;
    }
    return false;
}
static bool is_part_of_command_arguments(t_token *token)
{
    t_token *prev = NULL;

    // Traverse backwards to find the first command token
    for (prev = token; prev != NULL && prev->type == T_IDENTIFIER; prev = prev->prev) {
        if (is_command(prev->token)) {
            return true;  // The token is an argument to a command
        }
    }
    return false;  // No command token found before this, not a part of command arguments
}

void	join_identifier_tokens(t_token *lst)
{
    t_token	*curr;
    int		merged;

    merged = 1;
    while (merged)
    {
        merged = 0;
        curr = lst;
        while (curr != NULL && curr->next != NULL)
        {
            // Check if both tokens are not just simple identifiers but potentially commands and arguments
            if (curr->type == T_IDENTIFIER && curr->next->type == T_IDENTIFIER &&
                !is_command(curr->token) && !is_command(curr->next->token) &&
                !is_part_of_command_arguments(curr->next))
            {
                merge_identifier_tokens(curr);
                merged = 1;
                break;
            }
            curr = curr->next;
        }
    }
}