/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_s_play.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:06:05 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/14 00:00:54 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floor_and_ceiling_colors(t_data *data)
{
	int ceiling;
	int floor;

	ceiling = create_color_int(0, data->ceiling.red,
		data->ceiling.green, data->ceiling.blue);
	floor = create_color_int(0, data->floor.red,
		data->floor.green, data->floor.blue);
	data->ceiling.color = (unsigned int)ceiling;
	data->floor.color = (unsigned int)floor;
}

int		draw_labyrinth(t_imagedata *img, t_data *data)
{
	int	x;

	x = 0;
	while (x < data->screen.x)
	{
		algorithme(data, x);
		draw_column(data, x, img);
		x++;
	}
	sprite_drawing(data);
	if (data->save == 1)
		ft_save(data);
	return (0);
}

int		let_s_move(t_data *data)
{
	draw_labyrinth(&data->img, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	move(data);
	return (0);
}

int		let_s_play(t_data *data)
{
	if (!(data->mlx = mlx_init()))
		closing_error(data, 17);
	if (!(data->win = mlx_new_window(data->mlx, data->screen.x,
			data->screen.y, "Cub3D")))
		closing_error(data, 17);
	if (!(data->img.img = mlx_new_image(data->mlx, data->screen.x,
			data->screen.y)))
		closing_error(data, 17);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bit_per_pixel,
		&data->img.line_length, &data->img.endian);
	texture_creation(data);
	floor_and_ceiling_colors(data);
	mlx_hook(data->win, 2, 1L << 0, hit_key, data);
	mlx_hook(data->win, 3, 1L << 1, release_key, data);
	mlx_hook(data->win, 17, 1L << 2, closing, data);
	mlx_loop_hook(data->mlx, let_s_move, data);
	mlx_loop(data->mlx);
	return (0);
}
