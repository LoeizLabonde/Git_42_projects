/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_block.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:47:37 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/11 16:26:08 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub.h"

int	apply_attenuation(int color, float attenuation)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (int)(r * attenuation);
	g = (int)(g * attenuation);
	b = (int)(b * attenuation);
	return ((r << 16) | (g << 8) | b);
}

void	ft_block1(t_game *game, t_ray *ray, int i)
{
	int		texture_index;
	float	att;

	if (ft_touch(ray->ray_x, ray->ray_y, game) == 2)
		texture_index = 6;
	else
		texture_index = game->dir;
	game->calc.tex_x_coord = tex_x(ray->ray_x, ray->ray_y, game->side);
	game->calc.color = ft_get_texture(game->calc.tex_x_coord,
			(int)game->calc.tex_y, &game->img_tab[texture_index]);
	att = exp(-game->att_coef * game->calc.dist);
	game->calc.color = apply_attenuation(game->calc.color, att);
	ft_put_pixel_on_img(&game->img_tab[IMG], i,
		game->calc.start_y, game->calc.color);
}
