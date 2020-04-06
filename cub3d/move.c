/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:08:28 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/02 13:43:00 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void	forward(t_data *data)
{
	//si pas de rencontre mur
	//calcul nouveau x et y
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
	//si pas de rencontre mur
	//calcul nouveau x et y
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
	//si pas de rencontre mur
	//calcul nouveau x et y
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
	//si pas de rencontre mur
	//calcul nouveau x et y
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

void rotation_left(t_data *data)
{
	double olddirx;
	double oldplanex;

	olddirx = data->dir.x;
	data->dir.x = (data->dir.x * cos(-ROTSPEED)) - (data->dir.y * sin(-ROTSPEED));
	data->dir.y = (olddirx * sin(-ROTSPEED) + (data->dir.y * cos(-ROTSPEED)));
	oldplanex = data->plane.x;
	data->plane.x = (data->plane.x * cos(-ROTSPEED)) - (data->plane.y * sin(-ROTSPEED));
	data->plane.y = (oldplanex * sin(-ROTSPEED) + (data->plane.y * cos(-ROTSPEED)));
}

void rotation_right(t_data *data)
{
	double olddirx;
	double oldplanex;

	olddirx = data->dir.x;
	data->dir.x = (data->dir.x * cos(ROTSPEED)) - (data->dir.y * sin(ROTSPEED));
	data->dir.y = (olddirx * sin(ROTSPEED) + (data->dir.y * cos(ROTSPEED)));
	oldplanex = data->plane.x;
	data->plane.x = (data->plane.x * cos(ROTSPEED)) - (data->plane.y * sin(ROTSPEED));
	data->plane.y = (oldplanex * sin(ROTSPEED) + (data->plane.y * cos(ROTSPEED)));
}

int		move(t_data *data)
{
	if (data->move.up ==1)
		forward(data);
	if (data->move.down == 1)
		backward(data);
	if (data->move.left == 1)
		sideleft(data);
	if (data->move.right == 1)
		sideright(data);
	if (data->move .rot_l == 1)
		rotation_left(data);
	if (data->move .rot_r == 1)
		rotation_right(data);
		return (0);
}

int		let_s_move(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	move(data);
	if (!(data->img.img = mlx_new_image(data->mlx, data->screen.x, data->screen.y)))
		return (17);
	//data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bit_per_pixel, &data->img.line_length, &data->img.endian);
	zobizobi(&data->img, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);

}