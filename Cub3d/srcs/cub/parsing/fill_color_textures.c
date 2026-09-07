/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_color_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:41:28 by llabonde          #+#    #+#             */
/*   Updated: 2025/03/11 16:09:02 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub.h"

static void	copy_into_rgb_array(char **rgb_to_convert,
				int *rgb, t_game *data, int x)
{
	int		i;

	i = -1;
	while (rgb_to_convert[++i])
		rgb[i] = ft_atoi(rgb_to_convert[i]);
	free_tab((void **)rgb_to_convert);
	if (x == 1)
	{
		data->texinfo.ceiling_r = rgb [0];
		data->texinfo.ceiling_g = rgb [1];
		data->texinfo.ceiling_b = rgb [2];
	}
	else
	{
		data->texinfo.floor_r = rgb [0];
		data->texinfo.floor_g = rgb [1];
		data->texinfo.floor_b = rgb [2];
	}
	free(rgb);
}

static int	set_rgb_colors(char *line, t_game *data, int i)
{
	char	**rgb_to_convert;
	int		*rgb;
	int		count;

	rgb_to_convert = ft_split(line, ',');
	count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		free_tab((void **)rgb_to_convert);
		return (0);
	}
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return (0);
	}
	copy_into_rgb_array(rgb_to_convert, rgb, data, i);
	return (1);
}

int	fill_color_textures(t_game *data, t_texinfo *textures, char *line, int j)
{
	(void)textures;
	if (line[j] == 'C')
	{
		if (set_rgb_colors(line + j + 1, data, 1) == 0)
			return (err_msg(data->mapinfo.path, ERR_COLOR_CEILING, ERR));
	}
	else if (line[j] == 'F')
	{
		if (set_rgb_colors(line + j + 1, data, 0) == 0)
			return (err_msg(data->mapinfo.path, ERR_COLOR_FLOOR, ERR));
	}
	else
		return (err_msg(data->mapinfo.path, ERR_FLOOR_CEILING, ERR));
	return (SUCCESS);
}
