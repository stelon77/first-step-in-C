/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_part_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 11:48:38 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/10 19:04:48 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** variables for each column of the screen
*/

void	variable_value(t_data *data, int x)
{
	data->camerax = ((2 * x) / ((double)data->screen.x)) - 1;
	data->raydir.x = data->dir.x + (data->plane.x * data->camerax);
	data->raydir.y = data->dir.y + (data->plane.y * data->camerax);
	data->mapx = (int)data->pos.x;
	data->mapy = (int)data->pos.y;
	if (data->raydir.x == 0)
	{
		data->deltadist.x = 1;
		data->deltadist.y = 0;
	}
	else if (data->raydir.y == 0)
	{
		data->deltadist.x = 0;
		data->deltadist.y = 1;
	}
	else
	{
		data->deltadist.x = fabs(1 / data->raydir.x);
		data->deltadist.y = fabs(1 / data->raydir.y);
	}
}

/*
** calculate first side distance
** and step
*/

void	step_and_initial_sidedist(t_data *data)
{
	if (data->raydir.x < 0)
	{
		data->stepx = -1;
		data->sidedist.x = (data->pos.x - data->mapx) * data->deltadist.x;
	}
	else
	{
		data->stepx = 1;
		data->sidedist.x = (-data->pos.x + data->mapx + 1.0)
			* data->deltadist.x;
	}
	if (data->raydir.y < 0)
	{
		data->stepy = -1;
		data->sidedist.y = (data->pos.y - data->mapy) * data->deltadist.y;
	}
	else
	{
		data->stepy = 1;
		data->sidedist.y = (-data->pos.y + data->mapy + 1.0)
			* data->deltadist.y;
	}
}

/*
**	dda algorithm
**  jump to next mapsquare and check if wall hit
*/

void	perform_dda(t_data *data)
{
	data->hit = 0;
	while (data->hit == 0)
	{
		if (data->sidedist.x < data->sidedist.y)
		{
			data->sidedist.x += data->deltadist.x;
			data->mapx += data->stepx;
			data->side = 0;
		}
		else
		{
			data->sidedist.y += data->deltadist.y;
			data->mapy += data->stepy;
			data->side = 1;
		}
		if (data->map.map[(data->map.column * (data->mapy - 1))
				+ data->mapx - 1] == '1')
			data->hit = 1;
	}
}

/*
** distance from the hit to the screenplane
*/

void	calculate_distance(t_data *data)
{
	if (data->side == 0)
		data->perpwalldist = ((data->mapx - data->pos.x
			+ ((1 - data->stepx) / 2)) / data->raydir.x);
	else
		data->perpwalldist = ((data->mapy - data->pos.y
			+ ((1 - data->stepy) / 2)) / data->raydir.y);
}

/*
**	hight of wall in the x_column
*/

void	calculate_column(t_data *data)
{
	int	h;
	int	lineh;

	h = data->screen.y;
	lineh = (int)(h / data->perpwalldist);
	data->lineheight = lineh;
	data->drawstart = (h - lineh) / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = (h + lineh) / 2;
	if (data->drawend >= h)
		data->drawend = h - 1;
}
