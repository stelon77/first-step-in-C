/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:23:56 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/14 00:04:57 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_img_east(t_data *data)
{
	int width;
	int height;

	width = TEXWIDTH;
	height = TEXHEIGHT;
	if (!(data->texeast.img = mlx_xpm_file_to_image(data->mlx,
			data->east, &width, &height)))
		closing_error(data, 18);
	data->texeast.addr = mlx_get_data_addr(data->texeast.img,
			&data->texeast.bit_per_pixel, &data->texeast.line_length,
				&data->texeast.endian);
	return (0);
}

int	create_img_north(t_data *data)
{
	int width;
	int height;

	width = TEXWIDTH;
	height = TEXHEIGHT;
	if (!(data->texnorth.img = mlx_xpm_file_to_image(data->mlx,
			data->north, &width, &height)))
		closing_error(data, 18);
	data->texnorth.addr = mlx_get_data_addr(data->texnorth.img,
		&data->texnorth.bit_per_pixel, &data->texnorth.line_length,
			&data->texnorth.endian);
	return (0);
}

int	create_img_west(t_data *data)
{
	int width;
	int height;

	width = TEXWIDTH;
	height = TEXHEIGHT;
	if (!(data->texwest.img = mlx_xpm_file_to_image(data->mlx,
			data->west, &width, &height)))
		closing_error(data, 18);
	data->texwest.addr = mlx_get_data_addr(data->texwest.img,
		&data->texwest.bit_per_pixel, &data->texwest.line_length,
			&data->texwest.endian);
	return (0);
}

int	create_img_south(t_data *data)
{
	int width;
	int height;

	width = TEXWIDTH;
	height = TEXHEIGHT;
	if (!(data->texsouth.img = mlx_xpm_file_to_image(data->mlx,
			data->south, &width, &height)))
		closing_error(data, 18);
	data->texsouth.addr = mlx_get_data_addr(data->texsouth.img,
		&data->texsouth.bit_per_pixel, &data->texsouth.line_length,
			&data->texsouth.endian);
	return (0);
}

int	create_img_sprite(t_data *data)
{
	int width;
	int height;

	width = TEXWIDTH;
	height = TEXHEIGHT;
	if (!(data->texsprite.img = mlx_xpm_file_to_image(data->mlx,
			data->sprite, &width, &height)))
		closing_error(data, 18);
	data->texsprite.addr = mlx_get_data_addr(data->texsprite.img,
		&data->texsprite.bit_per_pixel, &data->texsprite.line_length,
			&data->texsprite.endian);
	return (0);
}
