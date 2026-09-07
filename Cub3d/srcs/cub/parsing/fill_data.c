/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:29:20 by llabonde          #+#    #+#             */
/*   Updated: 2025/03/08 11:35:51 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub.h"

static char	*get_texture_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

static int	fill_direction_textures(t_game *data, t_texinfo *textures,
				char *line, int j)
{
	if (line[j] == 'N' && line[j + 1] == 'O' && !(textures->north))
		textures->north = get_texture_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(textures->south))
		textures->south = get_texture_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(textures->west))
		textures->west = get_texture_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(textures->east))
		textures->east = get_texture_path(line, j + 2);
	else if (line[j] == 'F' )
	{
		if (fill_color_textures(data, textures, line, j) == ERR)
			return (ERR);
	}
	else if (line[j] == 'C')
	{
		if (fill_color_textures(data, textures, line, j) == ERR)
			return (ERR);
	}
	else
		return (ERR);
	return (SUCCESS);
}

static int	ignore_whitespaces_get_info(t_game *data, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (fill_direction_textures(data, &data->texinfo, map[i], j) == ERR)
		{
			free_tab((void **)data->mapinfo.file);
			ft_free_text(*data);
			return (err_msg(data->mapinfo.path, ERR_TEX_INVALID, FAILURE));
		}
		return (BREAK);
	}
	else if (ft_isdigit(map[i][j]))
	{
		if (create_map(data, map, i) == FAILURE)
		{
			free_tab((void **)data->map);
			free_tab((void **)data->mapinfo.file);
			ft_free_text(*data);
			return (err_msg(data->mapinfo.path, ERR_INVALID_MAP, FAILURE));
		}
		return (SUCCESS);
	}
	return (CONTINUE);
}

static int	checknull(char **map, char **info_file)
{
	if (map[0] == NULL)
	{
		free_tab((void **)info_file);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	get_file_data(t_game *data, char **map)
{
	int	i;
	int	j;
	int	ret;

	if (checknull(map, data->mapinfo.file) == FAILURE)
		return (FAILURE);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ret = ignore_whitespaces_get_info(data, map, i, j);
			if (ret == BREAK)
				break ;
			else if (ret == FAILURE)
				return (FAILURE);
			else if (ret == SUCCESS)
				return (SUCCESS);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
