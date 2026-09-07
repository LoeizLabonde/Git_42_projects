/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:23:14 by llabonde          #+#    #+#             */
/*   Updated: 2024/05/23 11:29:57 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<stdlib.h>

int	ft_get_start(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

int	ft_get_end(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, s1[len - i - 1]) == 0)
			break ;
		i++;
	}
	return (len - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*nstr;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start = ft_get_start(s1, set);
	end = ft_get_end(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	nstr = (char *)malloc(sizeof(char) * (end - start +1));
	if (nstr == NULL)
		return (NULL);
	ft_strlcpy(nstr, s1 + start, end - start + 1);
	return (nstr);
}
/*
int	ft_issep(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char    *ft_strcat(char *dest, char *src)
{
        unsigned int    i;
        unsigned int    dest_len;

        dest_len = ft_strlen(dest);
        i = 0;
        while (src[i] != '\0')
        {
                dest[dest_len + i] = src[i];
                i++;
        }
        dest[dest_len + i] = '\0';
        return (dest);
}

static char	*ft_str_n(size_t n)
{
	char	*str;

	str = (char *) malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		size;
	int		len;
	int		i;

	i = 0;
	size = ft_strlen(s1);
	while (ft_issep(s1[i], set) == 1 || s1[i] == (' ' | '\n' | '\t'))
		i++;
	while (ft_issep(s1[size], set) == 0 || s1[size] == (' ' | '\n' | '\t'))
		size--;
	if (i == size)
		return (ft_str_n(1));
	len = size - i;
	return (ft_substr(s1, i, len));
}*/