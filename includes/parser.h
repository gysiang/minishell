/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:21:45 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/27 18:54:12 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"

typedef struct s_ast_node
{
	char				*value;
	t_token_type		type;
	struct s_ast_node	*left_node;
	struct s_ast_node	*right_node;
}	t_ast_node;

int	ft_curr_token_is_operator(t_token *node);
int	ft_precedence(t_token *node);
t_token	*find_highest_op(t_token *token_lst);
t_ast_node	*make_ast_tree(t_token *token_lst);
void	print_ast_node(t_ast_node *node, int level);
void	print_ast_tree(t_ast_node *root);
t_ast_node *create_ast_node(t_token *token);
void	free_ast_tree(t_ast_node *ast_tree);

#endif
