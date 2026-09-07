/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:36:47 by kduroux           #+#    #+#             */
/*   Updated: 2025/02/26 10:04:34 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub.h"

int	check_file(char *path);
int	is_dir(char *path);
int	check_file(char *av);
int	is_cubfile(char *path);

int	check_file(char *av)
{
	int	fd;

	if (is_dir(av))
		return (printf("probleme directory\n"), -1);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (printf("probleme fd\n"), -1);
	if (close(fd) == -1)
		return (printf("probleme close\n"), -1);
	if (is_cubfile(av))
		return (printf("Wrong extensions\n"), -1);
	return (0);
}

int	is_cubfile(char *path)
{
	int	i;

	i = ft_strlen(path);
	if ((path[i - 4] != '.' || path[i - 3] != 'c')
		|| path[i - 2] != 'u' || path[i - 1] != 'b')
		return (1);
	return (0);
}

int	is_dir(char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		if (close(fd) == -1)
			return (printf("probleme close\n"));
		return (1);
	}
	return (0);
}
