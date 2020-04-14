/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 19:47:59 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/13 20:03:06 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_save(t_data *data, t_save *save)
{
	save->h = (int)data->screen.y;
	save->w = (int)data->screen.x;
	save->pad = (4 - ((save->w * 3) % 4)) % 4;
	create_file_header(data, save->pad, save->file_header);
	create_img_header(save->h, save->w, save->pad, save->img_header);
	return (0);
}

int		write_header(t_save *save)
{
	if ((write(save->fd, save->file_header, 14)) < 0)
	{
		close(save->fd);
		return (23);
	}
	if ((write(save->fd, save->img_header, 40)) < 0)
	{
		close(save->fd);
		return (23);
	}
	return (0);
}

int		write_picture(t_save *save, t_data *data)
{
	int				column;
	int				line;
	unsigned char	bgr[3];

	line = save->h - 1;
	while (line >= 0)
	{
		column = 0;
		while (column < save->w)
		{
			if ((write(save->fd, put_bgr(data, column, line, bgr), 3)) < 0)
				return (23);
			column++;
		}
		if (save->pad > 0)
			if ((write(save->fd, "\0\0\0", save->pad)) < 0)
				return (23);
		line--;
	}
	return (0);
}

void	ft_save(t_data *data)
{
	t_save	save;
	int		error;

	init_save(data, &save);
	if ((save.fd = open(SAVE, O_WRONLY | O_CREAT |
			O_TRUNC | O_APPEND, 0644)) < 0)
		closing_error(data, 22);
	if ((error = write_header(&save)))
		closing_error(data, error);
	if ((error = write_picture(&save, data)))
	{
		close(save.fd);
		closing_error(data, error);
	}
	close(save.fd);
	closing(data);
}

int		let_s_save(t_data *data)
{
	if (!(data->mlx = mlx_init()))
		closing_error(data, 17);
	if (!(data->img.img = mlx_new_image(data->mlx, data->screen.x,
			data->screen.y)))
		closing_error(data, 17);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bit_per_pixel,
		&data->img.line_length, &data->img.endian);
	texture_creation(data);
	floor_and_ceiling_colors(data);
	mlx_loop_hook(data->mlx, let_s_move, data);
	mlx_loop(data->mlx);
	return (0);
}
