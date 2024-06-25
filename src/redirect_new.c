/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 22:04:45 by gyong-si          #+#    #+#             */
/*   Updated: 2024/06/25 16:22:35 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_redirection(t_shell *minishell, t_token *curr)
{
    while (curr && check_redirection_type(curr))
    {
        if (curr->type == T_LESSER_THAN || curr->type == T_LEFT_SHIFT)
        {
            if (redirect_input(minishell, curr) == -1)
            {
                minishell_error_msg(curr->next->token, errno);
                return (0);
            }
        }
        else if (curr->type == T_GREATER_THAN || curr->type == T_RIGHT_SHIFT)
        {
            if (redirect_output(minishell, curr) == -1)
            {
                minishell_error_msg(curr->next->token, errno);
                return (0);
            }
        }
        curr = curr->next->next;
    }
    return (1);
}
/** *
cat <missing >test.txt

1. loop through the tokenlst for all the redirections
2. handle all the redirections in the tokenlst
3. handle all the commands and pipes next

void	pipex(t_shell *minishell)
{
	t_token	*curr;

	redir_lst = minishell->cmd_list;
	// first loop to handle
	while (redir_lst != NULL)
	{
		if (check)
	}
	wait_for_all_commands(minishell);
}
**/

int	redirect_input(t_token *lst, t_shell *mini)
{
	int		fd;
	int		type;
	char	*file;

	fd = -1;
	type = lst->type;
	file = lst->next->token;
	if (lst->next && lst->next->next && lst->next->type == T_FILE
			&& lst->next->next->type == T_IDENTIFIER)
		file = lst->next->next->token;
	if (type == T_LESSER_THAN)
		fd = open_input(file);
	else
		fd = here_doc(mini, file, 1);
	if (fd == -1)
	{
		mini->last_return = 1;
		exit(1);
		return (-1);
	}
	else
		mini->input_fd = fd;
	return (fd);
}

void	remove_tokens(t_token **token_lst, t_token *start_token, int num)
{
	t_token	*curr;
	t_token	*next_token;
	int		i;

	i = 0;
	curr = start_token;
	if (start_token == NULL || token_lst == NULL || *token_lst == NULL)
		return;
	while (i++ < num)
	{
		if (curr == NULL)
			break;
		if (curr->prev != NULL)
			curr->prev->next = curr->next;
		if (curr->next != NULL)
			curr->next->prev = curr->prev;
		if (*token_lst == curr)
			*token_lst = curr->next;
		next_token = curr->next;
		free(curr->token);
		free(curr);
		curr = next_token;
	}
}

static int handle_input(t_token *lst, t_shell *mini)
{
	t_token *head;
	int		flag;

	flag = 0;
	head = mini->cmd_list;
	if (redirect_input(lst, mini) != -1)
	{
		dup2(mini->input_fd, STDIN_FILENO);
		close(mini);
	}
	// free and remove the tokens
	if (lst->next && lst->next->next && lst->next->type == T_FILE
			&& lst->next->next->type == T_IDENTIFIER)
		flag = 1;

	rm_token(head, lst);
	rm_token(head, lst->next);
	if (flag)
		rm





}

static void	handle_output(t_token *lst, t_shell *mini)
{

}

void	pipex(t_shell *mini)
{
	t_token	*redir_lst;
	t_token	*exec_lst;

	redir_lst = mini->cmd_list;
	// first loop to handle redirections
	while (redir_lst != NULL)
	{
		if (redir_lst->type == T_LESSER_THAN || redir_lst->type == T_LEFT_SHIFT)
		{
			handle_input(redir_lst, mini);
		}
		else if (redir_lst->type == T_GREATER_THAN || redir_lst->type == T_RIGHT_SHIFT)
		{
			handle_output(redir_lst, mini);
		}
		redir_lst = redir_lst->next;
	}
	wait_for_all_commands(mini);
}
