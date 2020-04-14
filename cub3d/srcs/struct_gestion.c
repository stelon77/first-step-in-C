/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 11:37:25 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/10 19:25:03 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initialize_struct2(t_data *data)
{
	data->movespeed = MOVESPEED;
	data->rotspeed = ROTSPEED;
	data->numsprite = 0;
	data->spritepos = NULL;
	data->spriteorder = NULL;
	data->spritedistance = NULL;
	data->move.down = 0;
	data->move.up = 0;
	data->move.left = 0;
	data->move.rot_l = 0;
	data->move.right = 0;
	data->move.rot_r = 0;
	data->mlx = NULL;
	data->win = NULL;
	data->img.img = NULL;
	data->texeast.img = NULL;
	data->texnorth.img = NULL;
	data->texsouth.img = NULL;
	data->texsprite.img = NULL;
	data->texwest.img = NULL;
	data->currenttex.img = NULL;
}

void		initialize_struct(t_data *data)
{
	data->flag = 0;
	data->screen.x = 0;
	data->screen.y = 0;
	data->pos.x = 0;
	data->pos.y = 0;
	data->dir.x = 0;
	data->dir.y = 0;
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->sprite = NULL;
	data->map.map = NULL;
	data->error = 0;
	initialize_struct2(data);
}

static void	free_struct3(t_data *data)
{
	if (data->spritedistance)
	{
		free(data->spritedistance);
		data->spritedistance = NULL;
	}
}

static void	free_struct2(t_data *data)
{
	if (data->sprite)
	{
		free(data->sprite);
		data->sprite = NULL;
	}
	if (data->map.map)
	{
		free(data->map.map);
		data->map.map = NULL;
	}
	if (data->spritepos)
	{
		free(data->spritepos);
		data->spritepos = NULL;
	}
	if (data->spriteorder)
	{
		free(data->spriteorder);
		data->spriteorder = NULL;
	}
	free_struct3(data);
}

void		free_struct(t_data *data)
{
	if (data->north)
	{
		free(data->north);
		data->north = NULL;
	}
	if (data->south)
	{
		free(data->south);
		data->south = NULL;
	}
	if (data->west)
	{
		free(data->west);
		data->west = NULL;
	}
	if (data->east)
	{
		free(data->east);
		data->east = NULL;
	}
	free_struct2(data);
}
