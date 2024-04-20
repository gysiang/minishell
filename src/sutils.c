/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sutils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:35:11 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/20 19:38:44 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	handle_split(char ***ret, const char *s, int *i, int *n)
{
	int len;
	char *end_quote;

	len = 0;
	while (s[*i] == ' ')
		(*i)++;
	if (s[*i] == '"')
	{
		(*ret)[*n] = ft_strdup(&s[++(*i)]);
		end_quote = ft_strchr((*ret)[*n], '"');
		if (end_quote)
			(*i) += end_quote - (*ret)[*n] + 1;
	}
	else
	{
		len = ft_wordlen(&s[*i], ' ');
		(*ret)[*n] = ft_substr(s, *i, len);
	}
	(*i) += ft_wordlen(&s[*i], ' ') - 1;
	(*n)++;
}

char	**ft_dqsplit(char const *s, char c)
{
	int n;
	char **ret;
	int i;

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
			if (s[i] != c)
			{
				handle_split(&ret, s, &i, &n);
			}
		}
		ret[n] = NULL;
	}
	return (ret);
}

/***
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
			if (s[i] != c)
			{
				while (s[i] == ' ')
					i++;
				if (s[i] == '"')
				{
					ret[n] = ft_strdup(&s[++i]);
					end_quote = ft_strchr(ret[n], '"');
					if (end_quote)
						i += end_quote - ret[n] + 1;
				}
				else
				{
					int len = ft_wordlen(&s[i], c);
					ret[n] = ft_substr(s, i, len);
				}
				i = i + ft_wordlen(&s[i], c) - 1;
				n++;
			}
		}
		ret[n] = NULL;
	}
	return (ret);
} **/

void	convert_cmd(char **av)
{
	int i;
	int j;
	char	*combined;
	char	*tmp;

	i = 0;
	while (av[i] != NULL)
	{
		if (!strcmp(av[i], "|") && av[i + 1] != NULL && av[i + 2] != NULL)
		{
			tmp = ft_strjoin(av[i + 1], " ");
			combined = ft_strjoin(tmp, av[i + 2]);
			j = i + 3;
			while (av[j] != NULL)
			{
				av[j - 2] = av[j];
				j++;
			}
			av[i] = ft_strdup(combined);
			av[i + 1] = NULL;
			free(combined);
		}
		else
			i++;
	}
}
