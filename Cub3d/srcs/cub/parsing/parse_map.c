/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:14:44 by llabonde          #+#    #+#             */
/*   Updated: 2025/03/21 16:22:21 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub.h"

static int	check_top_or_bottom(char **map_tab, int i, int j)
{
	if (!map_tab || !map_tab[i] || !map_tab[i][j])
		return (FAILURE);
	while (map_tab[i][j] == ' ' || map_tab[i][j] == '\t'
	|| map_tab[i][j] == '\r' || map_tab[i][j] == '\v'
	|| map_tab[i][j] == '\f')
		j++;
	while (map_tab[i][j])
	{
		if (map_tab[i][j] != '1')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

int	check_map_sides(t_mapinfo *map, char **map_tab)
{
	int	i;
	int	j;

	if (check_top_or_bottom(map_tab, 0, 0) == FAILURE)
		return (FAILURE);
	i = 1;
	while (i < (map->height - 1))
	{
		j = ft_strlen(map_tab[i]) - 1;
		if (map_tab[i][j] != '1')
			return (FAILURE);
		i++;
	}
	if (check_top_or_bottom(map_tab, i, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	check_map_player(char **map_tab, int i, int j, int flag)
{
	if (map_tab[i][j] == 'N')
		flag++;
	else if (map_tab[i][j] == 'S')
		flag++;
	else if (map_tab[i][j] == 'E')
		flag++;
	else if (map_tab[i][j] == 'W')
		flag++;
	return (flag);
}

static int	check_map_elements(t_game *data, char **map_tab)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	data->player.angle = '0';
	while (map_tab[i] != NULL)
	{
		j = 0;
		while (map_tab[i][j])
		{
			while (cme(data, i, j))
				j++;
			if (!check_integrity(map_tab, i, j))
				return (err_msg(data->mapinfo.path, ERR_INV_LETTER, FAILURE));
			flag = check_map_player(map_tab, i, j, flag);
			if (flag > 1)
				return (err_msg(data->mapinfo.path, ERR_NUM_PLAYER, FAILURE));
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	check_map_validity(t_game *data, char **map_tab)
{
	if (!data->map)
		return (err_msg(data->mapinfo.path, ERR_MAP_MISSING, FAILURE));
	if (check_map_sides(&data->mapinfo, map_tab) == FAILURE)
	{
		free_tab((void **)data->map);
		return (err_msg(data->mapinfo.path, ERR_MAP_NO_WALLS, FAILURE));
	}
	if (data->mapinfo.height < 3)
	{
		free_tab((void **)data->map);
		return (err_msg(data->mapinfo.path, ERR_MAP_TOO_SMALL, FAILURE));
	}
	if (check_map_elements(data, map_tab) == FAILURE)
	{
		free_tab((void **)data->map);
		return (FAILURE);
	}
	return (SUCCESS);
}
