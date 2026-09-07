/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:02:50 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/20 15:08:03 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	open_fd(int i, int *fd, char *file)
{
	int	j;

	j = 0;
	fd[i] = open(file, O_RDONLY);
	if (fd[i] == -1)
	{
		while (j < i)
		{
			close(fd[j]);
			j++;
		}
		return (-1);
	}
	return (fd[i]);
}

void	ft_close_fd(int *fd)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (fd[i] != -1)
			close(fd[i]);
		i++;
	}
}

int	check_integrity(char **map_tab, int i, int j)
{
	int		flag;
	char	c;

	flag = 0;
	c = map_tab[i][j];
	if (c == '1' || c == '0' || c == 'S' || c == 'E'
		|| c == 'N' || c == 'W' || c == ' ' || c == '\n')
		flag = 1;
	if (c == 'P' || c == 'l' || c == 'x')
		flag = 1;
	return (flag);
}
