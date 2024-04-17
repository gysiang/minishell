/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:15:35 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/17 15:33:23 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/minishell.h"

// create a new node
t_node *create_node(char *token, t_token_type type)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->token = ft_strdup(token);
	new_node->type = type;
	new_node->next = NULL;
}

// add a node to end of linked list
void	add_node(t_node **head, char *token, t_token_type type)
{
	t_node *new_node;

	new_node = create_node(token, type);
	if (*head == NULL)
		*head = new_node;
	else
	{
		t_node *current_node = *head;
		while (current_node->next != NULL)
		{
			current_node = current_node->next;
		}
		current_node->next = new_node;
	}
}

// free the memory for linked list
void	free_tokenlist(t_node *head)
{
	t_node *current_node;
	t_node *tmp;

	current_node = head;
	while (current_node != NULL)
	{
		tmp = current_node;
		current_node = current_node->next;
		free (tmp->token);
		free(tmp);
	}
}
