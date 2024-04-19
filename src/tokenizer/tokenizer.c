/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:16:40 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/19 15:29:35 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_symbol_lst(char **line, t_token_type type, t_token **token_lst)
{
	t_token	*new_token;

	new_token = create_token(NULL, type);
	if (!new_token)
		return (0);
	// add the token to back of the token_lst
	token_add_back(token_lst, *line, type);
	// move to next char
	(*line)++;
	return (1);
}

static size_t	ft_wordlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	return (i);
}

int	add_command_lst(char **line, t_token **token_lst)
{
	t_token	*new_token;
	char	cmd[1000];

	//get the command
	ft_strlcat(cmd, *line, ft_wordlen(*line, ' '));
	printf("print cmd %s\n", cmd);
	// get from start of word to
	new_token = create_token(cmd, T_COMMAND);
	if (!new_token)
		return (0);
	token_add_back(token_lst, cmd, T_COMMAND);
	(*line) += ft_wordlen(*line, ' ');
	return (1);
}

t_token	*token_processor(char *line)
{
	t_token *token_lst;

	while (*line != '\0')
	{
		if (ft_iswhitespace(line))
			line++;
		else if (!ft_strcmp(line, "|"))
			add_symbol_lst(&line, T_PIPE, &token_lst);
		else
			add_command_lst(&line, &token_lst);
	}
	return (token_lst);
}

// print the linked list that holds the tokens;
void	print_tokenlst(t_token *token_lst)
{
	t_token *curr;

	curr = token_lst;
	while (curr != NULL)
	{
		printf("token: %s\n", curr->token);
		printf("token type: %d\n", curr->type);
		curr = curr->next;
	}
}

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
