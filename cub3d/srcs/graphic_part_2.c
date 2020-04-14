/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_part_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:06:23 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/14 00:02:26 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	calculate x of the hit on the wall
**	and the x corresponding in the texture
*/

void	calculate_wallx_and_x_text(t_data *data)
{
	if (data->side == 0)
		data->wallx = data->pos.y + (data->perpwalldist * data->raydir.y);
	else
	{
		data->wallx = data->pos.x + (data->perpwalldist * data->raydir.x);
	}
	data->wallx -= floor(data->wallx);
	data->texx = (int)(data->wallx * (double)TEXWIDTH);
	if (data->side == 0 && data->raydir.x < 0)
		data->texx = TEXWIDTH - data->texx - 1;
	if (data->side == 1 && data->raydir.y > 0)
		data->texx = TEXWIDTH - data->texx - 1;
}

/*
**	finding the y corresponding in the texture
**	extracting the color in the texture
**	putting that color at coordinates x and y
*/

int		find_textel_color_and_put(t_data *data, int x, t_imagedata *img)
{
	int				h;
	unsigned int	color;
	int				y;

	h = data->screen.y;
	data->step = 1.0 * TEXHEIGHT / data->lineheight;
	data->texpos = (data->drawstart - (h / 2)
		+ data->lineheight / 2) * data->step;
	y = data->drawstart;
	while (y < data->drawend)
	{
		data->texy = (int)data->texpos & (TEXHEIGHT - 1);
		data->texpos += data->step;
		color = my_texcolor_extractor(&data->currenttex,
			data->texx, data->texy);
		my_mlx_pixel_put(img, x, y, color);
		y++;
	}
	data->zbuffer[x] = data->perpwalldist;
	return (y);
}

/*
**	choose the right texture for wall
*/

void	wall_color_tex(t_data *data)
{
	if (data->side == 1 & data->stepy == 1)
		data->currenttex = data->texnorth;
	if (data->side == 1 & data->stepy == -1)
		data->currenttex = data->texsouth;
	if (data->side == 0 & data->stepx == 1)
		data->currenttex = data->texwest;
	if (data->side == 0 & data->stepx == -1)
		data->currenttex = data->texeast;
}

/*
**	sequence before drawing
*/

void	algorithme(t_data *data, int x)
{
	variable_value(data, x);
	step_and_initial_sidedist(data);
	perform_dda(data);
	calculate_distance(data);
	calculate_column(data);
	wall_color_tex(data);
}

void	draw_column(t_data *data, int x, t_imagedata *img)
{
	int	y;

	y = 0;
	while (y < data->screen.y)
	{
		if (y < data->drawstart)
			my_mlx_pixel_put(img, x, y, data->ceiling.color);
		if (y >= data->drawstart && y < data->drawend)
		{
			calculate_wallx_and_x_text(data);
			y = find_textel_color_and_put(data, x, img);
		}
		if (y >= data->drawend)
			my_mlx_pixel_put(img, x, y, data->floor.color);
		y++;
	}
}
