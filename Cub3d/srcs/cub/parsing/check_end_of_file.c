/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end_of_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:15:40 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/21 16:23:37 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub.h"

static int	check_line_one(char **file, int i, int j, int flag)
{
	if (flag == 1)
	{
		if (file[i][j] != '1' && file[i][j] != ' '
			&& file[i][j] != '\t' && file[i][j] != '\n')
			return (1);
	}
	else
	{
		if (file[i][j] != ' ' && file[i][j] != '\t'
			&& file[i][j] != '\n')
			return (1);
	}
	return (0);
}

static int	find_last_line_one(t_game *data, int map_end_line, int i, int j)
{
	int	is_map_line;

	while (i < data->mapinfo.line_count)
	{
		j = 0;
		if (data->mapinfo.file[i][j] == '\0')
		{
			i++;
			continue ;
		}
		is_map_line = 1;
		while (data->mapinfo.file[i][j])
		{
			if (check_line_one(data->mapinfo.file, i, j, 1))
			{
				is_map_line = 0;
				break ;
			}
			j++;
		}
		if (is_map_line)
			map_end_line = i;
		i++;
	}
	return (map_end_line);
}

static int	is_last_word(t_game *data, int i, int j)
{
	while (i < data->mapinfo.line_count)
	{
		j = 0;
		if (data->mapinfo.file[i][j] == '\0')
		{
			i++;
			continue ;
		}
		while (data->mapinfo.file[i][j])
		{
			if (check_line_one(data->mapinfo.file, i, j, 0))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_end_of_file(t_game *data)
{
	int	i;
	int	j;
	int	map_end_line;

	i = 0;
	j = 0;
	map_end_line = -1;
	map_end_line = find_last_line_one(data, map_end_line, i, j);
	if (map_end_line == -1)
		return (1);
	i = map_end_line + 1;
	if (is_last_word(data, i, j))
		return (1);
	return (0);
}
