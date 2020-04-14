/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:08:28 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/10 11:37:50 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	forward(t_data *data)
{
	int x;
	int y;

	x = (int)(data->pos.x + data->dir.x * MOVESPEED);
	y = (int)data->pos.y;
	if ((data->map.map[((data->map.column * (y - 1)) + x - 1)]) == '0')
		data->pos.x += data->dir.x * MOVESPEED;
	y = (int)(data->pos.y + data->dir.y * MOVESPEED);
	x = (int)data->pos.x;
	if ((data->map.map[((data->map.column * (y - 1)) + x - 1)]) == '0')
		data->pos.y += data->dir.y * MOVESPEED;
}

void	backward(t_data *data)
{
	int x;
	int y;

	x = (int)(data->pos.x - data->dir.x * MOVESPEED);
	y = (int)data->pos.y;
	if ((data->map.map[((data->map.column * (y - 1)) + x - 1)]) == '0')
		data->pos.x -= data->dir.x * MOVESPEED;
	y = (int)(data->pos.y - data->dir.y * MOVESPEED);
	x = (int)data->pos.x;
	if ((data->map.map[((data->map.column * (y - 1)) + x - 1)]) == '0')
		data->pos.y -= data->dir.y * MOVESPEED;
}

void	sideleft(t_data *data)
{
	int x;
	int y;

	x = (int)(data->pos.x - data->plane.x * MOVESPEED);
	y = (int)data->pos.y;
	if ((data->map.map[((data->map.column * (y - 1)) + x - 1)]) == '0')
		data->pos.x -= data->plane.x * MOVESPEED;
	y = (int)(data->pos.y - data->plane.y * MOVESPEED);
	x = (int)data->pos.x;
	if ((data->map.map[((data->map.column * (y - 1)) + x - 1)]) == '0')
		data->pos.y -= data->plane.y * MOVESPEED;
}

void	sideright(t_data *data)
{
	int x;
	int y;

	x = (int)(data->pos.x + data->plane.x * MOVESPEED);
	y = (int)data->pos.y;
	if ((data->map.map[((data->map.column * (y - 1)) + x - 1)]) == '0')
		data->pos.x += data->plane.x * MOVESPEED;
	y = (int)(data->pos.y + data->plane.y * MOVESPEED);
	x = (int)data->pos.x;
	if ((data->map.map[((data->map.column * (y - 1)) + x - 1)]) == '0')
		data->pos.y += data->plane.y * MOVESPEED;
}
