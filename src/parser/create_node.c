/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:34:48 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/27 18:43:26 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create a new ast node
t_ast_node *create_ast_node(t_token *token)
{
	t_token *new_node;

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
}
