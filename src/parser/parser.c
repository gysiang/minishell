
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:54:35 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/27 14:46:27 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
1. check if curr token is an operator, returns 1 if true
2. returns 0 if false;
*/

/**
int	ft_curr_token_is_operator(t_token *node)
{
	if (node->type == T_PIPE || node->type == T_AND || node->type == T_OR)
		return (1);
	return (0);
}

int	ft_precedence(t_token *node)
{
	if (node->type == T_OR || node->type == T_AND)
		return (0);
	return (1);
}
**/

/**
1. Iterates through token_lst to check for operator
2. Assign precedence to the token
3. if the precedence is higer than the highest, the node becomes the hightest
4. return the address of the highest op
*/

/**
t_token	*find_highest_op(t_token *token_lst)
{
	t_token *highest_op;
	int	highest_prec;
	int	prec;

	highest_prec = -1;
	highest_op = NULL;
	while (token_lst)
	{
		if (ft_curr_token_is_operator(token_lst))
		{
			prec = ft_precedence(token_lst);
			if (prec > highest_prec)
			{
				highest_prec = prec;
				highest_op = token_lst;
			}
		}
		token_lst = token_lst->next;
	}
	return (highest_op);
}

t_ast_node 	*make_ast_tree(t_token *token_lst)
{
	//t_ast_node	*new_node;
	t_ast_node	*op_node;
	t_token		*op_token;

	if (!token_lst)
		return (NULL);
	op_token = find_highest_op(token_lst);
	if (!op_token)
		return (create_ast_node(token_lst));
	op_node = create_ast_node(op_token);
	if (!op_node)
		return (NULL);
	op_token->prev->next = NULL;
	op_token->next->prev = NULL;
	op_node->left_node = make_ast_tree(token_lst);
	op_node->right_node = make_ast_tree(op_token->next);
	free(op_token);
	return (op_node);
}


void	print_ast_node(t_ast_node *node, int level)
{
	if (node == NULL)
		return;
    // Print the current node at the given indentation level
	printf("%*s", level * 4, ""); // Adjust the spacing for indentation
	printf("Node: %s\n", node->value);
    // Recursively print the left and right nodes
	if (node->left_node != NULL)
	{
		printf("%*s", (level + 1) * 4, ""); // Adjust the spacing for indentation
		printf("Left:\n");
		print_ast_node(node->left_node, level + 1);
	}
	if (node->right_node != NULL)
	{
		printf("%*s", (level + 1) * 4, ""); // Adjust the spacing for indentation
		printf("Right:\n");
		print_ast_node(node->right_node, level + 1);
	}
}

void	print_ast_tree(t_ast_node *root)
{
    // Start printing from the root node with an initial indentation level of 0
	print_ast_node(root, 0);
}
**/

static	char 	*concat_token(const char *token1, const char *token2)
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

t_token *join_identifier_tokens(t_token *lst)
{
	char *joined;
	t_token *curr;
	t_token *next;
	int	merged;

	merged = 1;
	while (merged)
	{
		merged = 0;
		curr = lst;
		while (curr != NULL && curr->next != NULL)
		{
			if (curr->type == T_IDENTIFIER && curr->next->type == T_IDENTIFIER)
			{
				joined = concat_token(curr->token, curr->next->token);
				if (joined != NULL)
				{
					free(curr->token);
					free(curr->next->token);
					curr->token = joined;
					next = curr->next;
					curr->next = next->next;
					free(next);
				}
				merged = 1;
				break ;
			}
			curr = curr->next;
		}
	}
	return (lst);
}

int	parse_cmd_semicolon(t_token *token_lst)
{
	t_token *curr;
	char	*result;
	size_t	len;

	curr = token_lst;
	if (ft_strchr(curr->token, ';') != NULL)
	{
		len = ft_wordlen(curr->token, ';');
		result = (char *)malloc(len + 1);
		if (!result)
			return (-1);
		ft_strlcpy(result, curr->token, len);
		free(curr->token);
		curr->token = result;
		return (1);
	}
	return (0);
}

t_token *parse_tokens(t_token *token_lst)
{
	t_token *curr;

	curr = token_lst;
	//iterate through token_lst
	while (curr != NULL)
	{
		// call parse cmd semicolon
		// call parse $ value
	}
	join_identifier_tokens(token_lst);
}
