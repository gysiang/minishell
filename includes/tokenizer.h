/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:29:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/02 13:52:06 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

// token types
typedef enum s_token_type
{
	T_IDENTIFIER,
	T_PIPE,
	T_OR,
	T_AND,
	T_LESSER_THAN,
	T_GREATER_THAN,
	T_LEFT_SHIFT,
	T_RIGHT_SHIFT,
	T_OPENQUOTES,
	T_CLOSEQUOTES
}	t_token_type;

// token structure
typedef struct	s_token
{
	char			*token;
	int				argc;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

void	token_add_back(t_token **head, char *token, t_token_type type);
void	free_tokenlst(t_token *head);
void	print_tokenlst(t_token *token_lst);
int	ft_iswhitespace(char *line);
int	ft_isbackslash(char *line);
int	ft_issemicolon(char *line);
int	add_symbol_lst(char **line, t_token_type type, t_token **token_lst);
int	add_command_lst(char **line, t_token **token_lst);
char	*ft_copy(char *dest, const char *src, size_t n);
char	*ft_strcat(char *dest, const char *src);
size_t	ft_wordlen(const char *s, char c);
t_token *create_token(char *token, t_token_type type);
t_token	*token_processor(char *line);
t_token	*token_parser(t_token *lst);


#endif
