/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:31:06 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/20 15:18:16 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	set_img_addr(t_img *img);
void	create_img(t_game *data, t_img *img, char *filename);
void	create_images(t_game *data);

void	set_img_addr(t_img *img)
{
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_pp,
			&img->size_line, &img->endian);
	if (!img->addr)
		return ;
}

void	create_img(t_game *data, t_img *img, char *filename)
{
	if (filename)
		img->ptr = mlx_xpm_file_to_image(data->mlx, filename,
				&img->width, &img->height);
	else
		img->ptr = mlx_new_image(data->mlx,
				WINDOWS_WIDTH, WINDOWS_HEIGHT);
	set_img_addr(img);
}

void	create_images(t_game *data)
{
	create_img(data, &data->img_tab[NO], data->texinfo.north);
	create_img(data, &data->img_tab[SO], data->texinfo.south);
	create_img(data, &data->img_tab[EA], data->texinfo.east);
	create_img(data, &data->img_tab[WE], data->texinfo.west);
	create_img(data, &data->img_tab[DOOR], "texture/door.xpm");
	create_img(data, &data->img_tab[MM], NULL);
	create_img(data, &data->img_tab[BG], NULL);
	create_img(data, &data->img_tab[IMG], NULL);
}
