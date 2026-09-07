/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:24:34 by kduroux           #+#    #+#             */
/*   Updated: 2025/02/26 10:04:34 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub.h"

t_img	ft_init_img(void);
t_img	*ft_init_img_tab(void);

t_img	ft_init_img(void)
{
	t_img	img;

	img.ptr = NULL;
	img.addr = NULL;
	img.width = 0;
	img.height = 0;
	img.bits_pp = 0;
	img.size_line = 0;
	img.endian = 0;
	return (img);
}

t_img	*ft_init_img_tab(void)
{
	t_img	*img_tab;
	int		i;

	img_tab = malloc(IMG_TAB * sizeof(t_img));
	if (!img_tab)
		err_msg(ERR_MALLOC, "", 0);
	i = 0;
	while (i < IMG_TAB)
		img_tab[i++] = ft_init_img();
	return (img_tab);
}
