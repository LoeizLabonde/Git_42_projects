/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:23:56 by llabonde          #+#    #+#             */
/*   Updated: 2025/03/11 16:26:02 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub.h"

void	ft_draw_background(t_game *game);
int		ft_get_texture(int i, int start_y, t_img *img);
int		tex_x(float ray_x, float ray_y, int side);
void	ft_put_pixel_on_img(t_img *img, int x, int y, int color);

void	ft_put_pixel_on_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= WINDOWS_WIDTH || x < 0 || y >= WINDOWS_HEIGHT || y < 0)
		return ;
	dst = img->addr + (y * img->size_line + x * (img->bits_pp / 8));
	*(unsigned int *)dst = color;
}

int	tex_x(float ray_x, float ray_y, int side)
{
	double	wall_x;

	if (side == 1)
		wall_x = ray_x / BLOCK;
	else
		wall_x = ray_y / BLOCK;
	wall_x -= floor((wall_x));
	return ((int)(wall_x * (float)(TEXW)));
}

int	ft_get_texture(int tex_x, int tex_y, t_img *img)
{
	unsigned char	color_b;
	unsigned char	color_g;
	unsigned char	color_r;
	int				rgb;

	color_b = img->addr[tex_y
		* img->size_line + tex_x * (img->bits_pp / 8)];
	color_g = img->addr[tex_y
		* img->size_line + tex_x * (img->bits_pp / 8) + 1];
	color_r = img->addr[tex_y
		* img->size_line + tex_x * (img->bits_pp / 8) + 2];
	rgb = color_r;
	rgb = (rgb << 8) + color_g;
	rgb = (rgb << 8) + color_b;
	return (rgb);
}

void	ft_draw_background(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x++ < WINDOWS_WIDTH)
	{
		y = 0;
		while (y++ < WINDOWS_HEIGHT)
		{
			if (y < WINDOWS_HEIGHT / 2)
				ft_put_pixel_on_img(&game->img_tab[BG], x, y,
					rgbtohex(game->texinfo.ceiling_r, game->texinfo.ceiling_g,
						game->texinfo.ceiling_b));
			else
				ft_put_pixel_on_img(&game->img_tab[BG], x, y,
					rgbtohex(game->texinfo.floor_r, game->texinfo.floor_g,
						game->texinfo.floor_b));
		}
	}
}
