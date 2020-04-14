/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_vectors_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 11:28:46 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/07 22:46:20 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_north(t_data *data)
{
	data->flag |= NORTH;
	data->dir.x = 0;
	data->dir.y = -1;
	data->plane.x = POV;
	data->plane.y = 0;
}

static void	init_south(t_data *data)
{
	data->flag |= SOUTH;
	data->dir.x = 0;
	data->dir.y = 1;
	data->plane.x = -POV;
	data->plane.y = 0;
}

static void	init_west(t_data *data)
{
	data->flag |= WEST;
	data->dir.x = -1;
	data->dir.y = 0;
	data->plane.x = 0;
	data->plane.y = -POV;
}

static void	init_east(t_data *data)
{
	data->flag |= EAST;
	data->dir.x = 1;
	data->dir.y = 0;
	data->plane.x = 0;
	data->plane.y = POV;
}

void		player_vectors_init(t_data *data, char direction, int i)
{
	data->flag |= PLAYER;
	data->pos.x = (i % data->map.column) + 1.5;
	data->pos.y = (i / data->map.column) + 1.5;
	if (direction == 'N')
		init_north(data);
	if (direction == 'S')
		init_south(data);
	if (direction == 'W')
		init_west(data);
	if (direction == 'E')
		init_east(data);
	data->map.map[i] = '0';
}
