/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:33:25 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/19 12:47:18 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if character is space
int	ft_iswhitespace(char *line)
{
	if (*line == ' ' || *line == '"')
		return (1);
	return (0);
}
