/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:33:25 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/03 16:11:56 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if character is space
int	ft_iswhitespace(char *line)
{
	if (*line == ' ')
		return (1);
	return (0);
}

int	ft_isbackslash(char *line)
{
	if (*line == '\\')
		return (1);
	return (0);
}

int	ft_issemicolon(char *line)
{
	if (*line == ';')
	{
		return (1);
	}
	return (0);
}

char *ft_copy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*ptr)
		ptr++;
	while (*src)
	{
		*ptr++ = *src++;
	}
	*ptr = '\0';
	return (dest);
}

// print the linked list that holds the tokens;
void	print_tokenlst(t_token *token_lst)
{
	t_token *curr;

	curr = token_lst;
	printf("entered into print_tokenlst\n");
	while (curr != NULL)
	{
		printf("token: %s\n", curr->token);
		printf("token type: %d\n", curr->type);
		curr = curr->next;
	}
}

char	*remove_sq_dq(char **line)
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
}
