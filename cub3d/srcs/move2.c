/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 11:32:38 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/10 11:41:13 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotation_left(t_data *data)
{
	double olddirx;
	double oldplanex;

	olddirx = data->dir.x;
	data->dir.x = (data->dir.x * cos(-ROTSPEED))
		- (data->dir.y * sin(-ROTSPEED));
	data->dir.y = (olddirx * sin(-ROTSPEED)
		+ (data->dir.y * cos(-ROTSPEED)));
	oldplanex = data->plane.x;
	data->plane.x = (data->plane.x * cos(-ROTSPEED))
		- (data->plane.y * sin(-ROTSPEED));
	data->plane.y = (oldplanex * sin(-ROTSPEED)
		+ (data->plane.y * cos(-ROTSPEED)));
}

void	rotation_right(t_data *data)
{
	double olddirx;
	double oldplanex;

	olddirx = data->dir.x;
	data->dir.x = (data->dir.x * cos(ROTSPEED)) - (data->dir.y * sin(ROTSPEED));
	data->dir.y = (olddirx * sin(ROTSPEED) + (data->dir.y * cos(ROTSPEED)));
	oldplanex = data->plane.x;
	data->plane.x = (data->plane.x * cos(ROTSPEED))
		- (data->plane.y * sin(ROTSPEED));
	data->plane.y = (oldplanex * sin(ROTSPEED)
		+ (data->plane.y * cos(ROTSPEED)));
}

int		move(t_data *data)
{
	if (data->move.up == 1)
		forward(data);
	if (data->move.down == 1)
		backward(data);
	if (data->move.left == 1)
		sideleft(data);
	if (data->move.right == 1)
		sideright(data);
	if (data->move.rot_l == 1)
		rotation_left(data);
	if (data->move.rot_r == 1)
		rotation_right(data);
	return (0);
}
