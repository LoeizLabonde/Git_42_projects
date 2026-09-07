/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llabonde <llabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:33:28 by llabonde          #+#    #+#             */
/*   Updated: 2024/06/28 15:58:54 by llabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*ft_get_read_file(int fd, char *str)
{
	int			byte_read;
	char		*buff;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		if (!str)
			str = ft_strdup("");
		byte_read = read(fd, buff, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(str), free(buff), NULL);
		if (byte_read == 0 && !*str)
			return (free(str), free(buff), NULL);
		else if (!byte_read)
			break ;
		buff[byte_read] = '\0';
		str = ft_strjoin(str, buff);
		if (ft_strchr(str, '\n') == 1)
			break ;
	}
	return (free(buff), str);
}

char	*ft_get_nl(char *str)
{
	char	*stash;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == 0 || str[1] == 0)
		return (NULL);
	stash = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (*stash == 0)
	{
		free(stash);
		stash = NULL;
	}
	str[i + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*str;

	str = ft_get_read_file(fd, stash[fd]);
	if (BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_get_nl(str);
	return (str);
}

/*
int main(void)
{
	char	*line;
	int		i;
	int		fd1;

	fd1 = open("tests/test0.txt", O_RDONLY);
	i = 1;
	while (i < 6)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
		if (i == 2)
		{
			char *temp;
			do {
				temp = get_next_line(fd1);
				free(temp);
			} while (temp != NULL);
			close (fd1);
			fd1 = open("tests/test0.txt", O_RDONLY);
		}
	}
	close(fd1);
	return (0);
}

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("tests/test.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/