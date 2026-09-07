/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:51:57 by llabonde          #+#    #+#             */
/*   Updated: 2024/08/22 11:10:00 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdlib.h>

static size_t	ft_countwords(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static int	ft_splitcare(char **split, int i)
{
	int	j;

	j = 0;
	if (!split[i -1])
	{
		while (j < i - 1)
		{
			free(split[j]);
			j++;
		}
		free(split);
		return (1);
	}
	else
		return (0);
}

static int	ft_spliter(char **split, char *s, char c)
{
	int		i;
	size_t	word_len;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				word_len = ft_strlen(s);
			else
				word_len = ft_strchr(s, c) - s;
			split[i++] = ft_substr(s, 0, word_len);
			if (!split[i - 1])
			{
				if (ft_splitcare(split, i) == 1)
					return (0);
			}
			s += word_len;
		}
	}
	split[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	split = (char **)malloc((ft_countwords(s, c) + 1) * sizeof(char *));
	if (!split || !s)
		return (NULL);
	if (ft_spliter(split, (char *)s, c) == 0)
		return (NULL);
	return (split);
}
