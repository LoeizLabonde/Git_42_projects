/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:50:17 by kduroux           #+#    #+#             */
/*   Updated: 2024/05/28 13:15:18 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count_word(char const *s, char c)
{
	int	count;

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

static void	ft_free(char **tab, int i)
{
	int	j;

	j = 0;
	while (j < i - 1)
	{
		free(tab[j]);
		j++;
	}
	free(tab);
}

static int	ft_spliter(char **tab, char const *s, char c)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	while (i < count_word(s, c))
	{
		while (s[j] == c)
			j++;
		start = j;
		while (s[j] != c && s[j])
			j++;
		tab[i++] = ft_substr(s, start, j - start);
		if (!tab[i - 1])
			return (ft_free(tab, i), 0);
	}
	tab[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	tab = ft_calloc(count_word(s, c) + 1, sizeof(char *));
	if (!tab || !s)
		return (NULL);
	if (ft_spliter(tab, s, c) == 0)
		return (NULL);
	return (tab);
}
