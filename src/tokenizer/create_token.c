/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:36:29 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/20 19:38:19 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create a new node
t_token *create_token(char *token, t_token_type type)
{
	t_token *new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->token = token;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

// add a node to end of token list
void	token_add_back(t_token **head, char *token, t_token_type type)
{
	t_token *new_node;
	t_token *current_node;

	new_node = create_token(token, type);
	if (*head == NULL)
		*head = new_node;
	else
	{
		current_node = *head;
		while (current_node->next != NULL)
		{
			current_node = current_node->next;
		}
		current_node->next = new_node;
	}
}

// free the memory for linked list
void	free_tokenlst(t_token *head)
{
	t_token *current_node;
	t_token *tmp;

	current_node = head;
	while (current_node != NULL)
	{
		tmp = current_node;
		current_node = current_node->next;
		free (tmp->token);
		free(tmp);
	}
}
