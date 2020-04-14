/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 10:50:06 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/13 12:16:09 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sprite_sorting(int *order, double *dist, int amount)
{
	int		i;
	int		j;
	double	tempdist;
	int		temporder;

	i = 0;
	while (i < amount - 1)
	{
		j = 1;
		while ((i + j) < amount)
		{
			if (dist[i] < dist[i + j])
			{
				tempdist = dist[i];
				dist[i] = dist[i + j];
				dist[i + j] = tempdist;
				temporder = order[i];
				order[i] = order[i + j];
				order[i + j] = temporder;
			}
			j++;
		}
		i++;
	}
}

static void	sort_sprite(t_data *data)
{
	int		i;
	double	x;
	double	y;

	i = 0;
	while (i < data->numsprite)
	{
		x = data->pos.x - data->spritepos[i].x;
		y = data->pos.y - data->spritepos[i].y;
		data->spriteorder[i] = i;
		data->spritedistance[i] = (x * x) + (y * y);
		i++;
	}
	sprite_sorting(data->spriteorder, data->spritedistance, data->numsprite);
}

void		transform_sprite(t_data *data, int i)
{
	double	sp_x;
	double	sp_y;
	double	invdet;
	double	tr_x;
	double	tr_y;

	sp_x = data->spritepos[data->spriteorder[i]].x - data->pos.x;
	sp_y = data->spritepos[data->spriteorder[i]].y - data->pos.y;
	invdet = 1.0 / (data->plane.x * data->dir.y - data->plane.y * data->dir.x);
	tr_x = invdet * (data->dir.y * sp_x - data->dir.x * sp_y);
	tr_y = invdet * (data->plane.x * sp_y - data->plane.y * sp_x);
	data->transformx = tr_x;
	data->transformy = tr_y;
	data->spritescreenx = (int)((data->screen.x / 2) * (1 + (tr_x / tr_y)));
	data->spriteheight = abs((int)(data->screen.y / tr_y));
	data->spritewidth = abs((int)(data->screen.y / tr_y));
}

void		sprite_height_and_width(t_data *data)
{
	data->drawstarty = (data->screen.y - data->spriteheight) / 2;
	if (data->drawstarty < 0)
		data->drawstarty = 0;
	data->drawendy = (data->screen.y + data->spriteheight) / 2;
	if (data->drawendy >= data->screen.y)
		data->drawendy = data->screen.y - 1;
	data->drawstartx = data->spritescreenx - (data->spritewidth / 2);
	if (data->drawstartx < 0)
		data->drawstartx = 0;
	data->drawendx = data->spritescreenx + (data->spritewidth / 2);
	if (data->drawendx >= data->screen.x)
		data->drawendx = data->screen.x - 1;
}

int			sprite_drawing(t_data *data)
{
	int	i;

	sort_sprite(data);
	i = -1;
	while (++i < data->numsprite)
	{
		transform_sprite(data, i);
		if (data->transformy > 0)
		{
			sprite_height_and_width(data);
			draw_sprite_loop_x(data);
		}
	}
	return (0);
}
