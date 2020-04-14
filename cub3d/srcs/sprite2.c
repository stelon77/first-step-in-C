/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 12:15:25 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/13 23:48:58 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_sprite_loop_y(t_data *data, int x, int texx)
{
	int				y;
	int				texy;
	int				d;
	unsigned int	color;

	y = data->drawstarty;
	while (y < data->drawendy)
	{
		d = y * 256 - data->screen.y * 128 + data->spriteheight * 128;
		texy = ((d * TEXHEIGHT) / data->spriteheight) / 256;
		if (texy < 0)
			texy = 0;
		if (texy >= TEXHEIGHT)
			texy = TEXHEIGHT - 1;
		if ((color = my_texcolor_extractor(&data->texsprite, texx, texy)))
			my_mlx_pixel_put(&data->img, x, y, color);
		y++;
	}
}

void		draw_sprite_loop_x(t_data *data)
{
	int	x;
	int	texx;

	x = data->drawstartx;
	while (x < data->drawendx)
	{
		if (data->transformy < data->zbuffer[x])
		{
			texx = (int)(256 * (x - (-data->spritewidth / 2
				+ data->spritescreenx)) * TEXWIDTH / data->spritewidth) / 256;
			draw_sprite_loop_y(data, x, texx);
		}
		x++;
	}
}
