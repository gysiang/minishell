/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:35:11 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/13 12:14:25 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_wcount(char const *s, char c)
{
	int		n;

	n = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		while (*s && *s != c)
			s++;
		n++;
		while (*s && *s == c)
			s++;
	}
	return (n);
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

char **ft_dqsplit(char const *s, char c)
{
	int n;
	char **ret;
	int i;
	char *end_quote;

	i = -1;
	if (!s)
		return (NULL);
	n = ft_wcount(s, c);
	ret = malloc((n + 1) * sizeof(char *));
	n = 0;
	if (ret)
	{
		while (s[++i])
		{
			if (s[i] && s[i] != c)
			{
				while (s[i] == ' ')
					i++;
				if (s[i] == '"')
				{
					ret[n] = ft_strdup(&s[++i]);
					end_quote = ft_strchr(ret[n], '"');
					if (end_quote)
					{
						*end_quote = '\0';
						i += end_quote - ret[n] + 1;
					}
				}
				else
				{
					ret[n] = malloc(ft_wordlen(&s[i], c) + 1);
					strncpy(ret[n], &s[i], ft_wordlen(&s[i], c));
					ret[n][ft_wordlen(&s[i], c)] = '\0';
					i = i + ft_wordlen(&s[i], c) - 1;
				}
				i = i + ft_wordlen(&s[i], c) - 1;
				n++;
			}
		}
		ret[n] = NULL;
	}
	return (ret);
}
