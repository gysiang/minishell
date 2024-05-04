
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
/***
char	*remove_singlequote(char **line)
{
	char	*result;
	char	*str;
	int	i;
	int	j;

	i = 0;
	j = 0;
	str = *line;
	result = (char *)malloc(ft_strlen(*line) + 1);
	if (!result)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] !=  '\'')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
} **/

static void parse_singlequote(t_token *t)
{
	char	*result;
	char	*str;
	int	i;
	int j;

	i = 0;
	j = 0;
	str = t->token;
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return ;
	while (str[i] != '\0')
	{
		if (str[i] !=  '\'')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	free(t->token);
	t->token = result;
	return ;
}

static void parse_semicolon(t_token *token)
{
	t_token *curr;
	char *result;
	size_t len;

	curr = token;
	len = ft_wordlen(curr->token, ';');
	result = (char *)malloc(len + 1);
	if (!result)
		return;
	ft_copy(result, curr->token, len);
	free(curr->token);
	curr->token = result;
}

static void parse_value(t_token *token_lst, t_shell *minishell)
{
	t_token *curr;
	char *token;
	char *result;
	char *env_value;

	curr = token_lst;
	token = curr->token;
	if (token == NULL || token[0] != '$')
		return;
	result = ft_substr(token, 1, ft_strlen(token) - 1);
	if (!result)
		return ;
	env_value = my_getenv(result, minishell->env);
	free(result);
	if (!env_value)
		return;
	free(curr->token);
	curr->token = env_value;
}


t_token *token_parser(t_token *token_lst, t_shell *minishell)
{
	t_token *curr;

	curr = token_lst;
	while (curr != NULL)
	{
		if (ft_strchr(curr->token, '\''))
			parse_singlequote(curr);
		else if (ft_strchr(curr->token, ';'))
			parse_semicolon(curr);
		else if (ft_strchr(curr->token, '$'))
			parse_value(curr, minishell);
		curr = curr -> next;
	}
	join_identifier_tokens(token_lst);
	return (token_lst);
}

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
