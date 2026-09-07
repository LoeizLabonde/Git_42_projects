/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:47:57 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/11 16:12:36 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub.h"

void	ft_draw_ray(t_game *game, float start_x, int i);
void	ft_set_dir(t_game *game, t_ray *ray);
void	ft_raycast(t_game *game, t_ray *ray, int i);

void	ft_init_calc(t_game *game, t_ray *ray)
{
	game->calc.dist = fixed_dist(ray->ray_x, ray->ray_y, game);
	game->calc.height = (BLOCK / game->calc.dist) * ((float)WINDOWS_WIDTH / 2);
	game->calc.start_y = (WINDOWS_HEIGHT - game->calc.height) / 2;
	game->calc.step = (float)TEXH / game->calc.height;
	game->calc.end = game->calc.start_y + game->calc.height;
	game->calc.tex_y = 0;
}

void	ft_raycast(t_game *game, t_ray *ray, int i)
{
	ft_init_calc(game, ray);
	while (game->calc.start_y < game->calc.end)
	{
		ft_block1(game, ray, i);
		game->calc.tex_y += game->calc.step;
		game->calc.start_y++;
	}
}

void	ft_set_dir(t_game *game, t_ray *ray)
{
	if (game->side == 0)
	{
		if (ray->ray_dir_x > 0)
			game->dir = EA;
		else
			game->dir = WE;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			game->dir = SO;
		else
			game->dir = NO;
	}
}

void	ft_draw_ray(t_game *game, float start_x, int i)
{
	t_ray	*ray;

	ray = &game->ray;
	ft_init_ray(ray, game, start_x);
	while (42)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->ray_x += ray->step_x;
			game->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->ray_y += ray->step_y;
			game->side = 1;
		}
		if (ft_touch(ray->ray_x, ray->ray_y, game) > 0)
			break ;
	}
	ft_set_dir(game, ray);
	ft_raycast(game, ray, i);
}
