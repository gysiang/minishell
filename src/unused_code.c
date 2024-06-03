/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:34:48 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/03 13:17:46 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create a new ast node
/**
t_ast_node *create_ast_node(t_token *token)
{
	t_ast_node *new_node;

	new_node = malloc(sizeof(t_ast_node));
	if (!new_node)
		return (NULL);
	new_node->value = ft_strdup(token->token);
	new_node->type = token->type;
	new_node->left_node = NULL;
	new_node->right_node = NULL;
	return (new_node);
}

// free the ast tree
void	free_ast_tree(t_ast_node *ast_tree)
{
	if (ast_tree == NULL)
		return ;
	free_ast_tree(ast_tree->left_node);
	free_ast_tree(ast_tree->right_node);
	free(ast_tree->value);
	free(ast_tree);
} **/

/***
void execute_builtins(t_token *curr, t_shell *minishell)
{
    int pid;

    if (ft_strncmp(curr->token, "exit", 4) == 0 ||
        ft_strncmp(curr->token, "export", 6) == 0 ||
        ft_strncmp(curr->token, "unset", 5) == 0)
    {
        execute_builtin_2(curr, minishell);
    }
    else
    {
        pid = fork();
        if (pid == 0)
        {
            if (ft_strncmp(curr->token, "cd", 2) == 0 ||
                ft_strncmp(curr->token, "echo", 4) == 0 ||
                ft_strncmp(curr->token, "env", 3) == 0)
            {
                execute_builtin_1(curr, minishell);
            }
            other_cmds(curr, minishell);
            exit(0);
        }
        else
            minishell->process_ids[minishell->process_count++] = pid;
    }
}

void pipex(t_shell *minishell)
{
    int i;
    t_token *curr;
    t_token *start_cmd;
    int token_count;

    i = 0;
    curr = minishell->cmd_list;
    while (curr != NULL)
    {
        token_count = count_tokens(minishell); // Count tokens at the start of command processing
        printf("Total tokens: %d\n", token_count); // Display the total number of tokens

        if (check_redirection_type(curr))
            curr = curr->next;
        else if (curr->type == T_IDENTIFIER)
        {
            start_cmd = curr; // Start of a new command
            while (curr->next && curr->next->type == T_IDENTIFIER)
            {
                curr = curr->next; // Move to the end of the command arguments
            }
            execute_builtins_or_exc(i++, start_cmd, minishell); // Execute the whole command with arguments
        }
        curr = curr->next;
    }
    wait_for_all_commands(minishell);
    restore_fds(minishell->input_fd, minishell->output_fd);
}

static void	execute_builtins_or_exec(int i, t_token *curr, t_shell *minishell)
{
	if (check_builtin(curr->token))
	{
		execute_builtins(curr, minishell);
	}
	else
		execute_command(i, curr, minishell);
}

void	execute_without_redirection(t_shell *minishell)
{
	int		i;
	int		num;
	t_token	*curr;

	i = 0;
	num = 0;
	curr = minishell->cmd_list;
	printf("execute without redirections\n");
	while (curr != NULL)
	{
		if (curr->type == T_IDENTIFIER)
		{
			if (ft_strcmp(curr->token, "echo") == 0)
			{
				num = num_of_arguments(minishell);
				printf("number of arguments %d\n", num);
			}
			execute_builtins_or_exec(i++, curr, minishell);
			while (num > 0)
			{
				curr = curr->next;
				num--;
			}
		}
		curr = curr->next;
	}
}

void	pipex(t_shell *minishell)
{
	int	index;
	int token_count;

	index = check_for_redirections(minishell);
	token_count = count_tokens(minishell);
	printf("Total tokens: %d\n", token_count);
	if (index > 0)
		execute_with_redirection(minishell, index);
	else
		execute_without_redirection(minishell);
	wait_for_all_commands(minishell);
	restore_fds(minishell->input_fd, minishell->output_fd);
} **/
