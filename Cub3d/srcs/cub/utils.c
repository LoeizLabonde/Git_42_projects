/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kduroux <kduroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:33:49 by kduroux           #+#    #+#             */
/*   Updated: 2025/03/20 15:10:45 by kduroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int		check_texture_validity(t_game *data, t_texinfo texinfo);
int		*check_texture_validity_utils(t_texinfo texinfo, int *fd);
int		parse_file(char **av, int ac, t_game *data);
int		err_msg(char *detail, char *str, int code);
void	free_tab(void **tab);

int	parse_file(char **av, int ac, t_game *data)
{
	(void)ac;
	if (check_file(av[1]) == -1)
		return (1);
	if (parse_data(av[1], data))
		return (1);
	if (get_file_data(data, data->mapinfo.file))
		return (1);
	if (check_map_validity(data, data->map))
	{
		ft_free_parse(*data);
		return (1);
	}
	if (check_texture_validity(data, data->texinfo))
	{
		free_tab((void **)data->map);
		ft_free_parse(*data);
		return (1);
	}
	return (0);
}

int	*check_texture_validity_utils(t_texinfo texinfo, int *fd)
{
	if (texinfo.west)
	{
		if (open_fd(0, fd, texinfo.west) < 0)
			return (0);
	}
	if (texinfo.east)
	{
		if (open_fd(1, fd, texinfo.east) < 0)
			return (0);
	}
	if (texinfo.north)
	{
		if (open_fd(2, fd, texinfo.north) < 0)
			return (0);
	}
	if (texinfo.south)
	{
		if (open_fd(3, fd, texinfo.south) < 0)
			return (0);
	}
	return (fd);
}

int	check_texture_validity(t_game *data, t_texinfo texinfo)
{
	int	fd[4];
	int	i;

	i = 0;
	if (check_texture_validity_utils(texinfo, fd) == 0)
		return (err_msg(data->mapinfo.path, ERR_TEX_INVALID, FAILURE));
	ft_close_fd(fd);
	while (i < 4)
	{
		if (fd[i] == -1)
			return (err_msg(data->mapinfo.path, ERR_TEX_INVALID, FAILURE));
		i++;
	}
	return (0);
}

int	err_msg(char *detail, char *str, int code)
{
	ft_putstr_fd("cub3D: Error", 2);
	if (detail)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(detail, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n", 2);
	return (code);
}

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}
