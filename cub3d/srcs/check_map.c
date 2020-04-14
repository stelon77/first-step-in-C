/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 23:51:35 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/10 11:30:03 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** creating field for each sprite
*/

int		create_sprite_data(t_data *data, int n)
{
	if (!(data->spritepos = (t_xy *)malloc(sizeof(t_xy) * n)))
		return (0);
	if (!(data->spriteorder = (int *)malloc(sizeof(int) * n)))
		return (0);
	if (!(data->spritedistance = (double *)malloc(sizeof(double) * n)))
		return (0);
	return (1);
}

/*
** check point
**
** cheking closed map (no space around datas except 1)
** if sprite, keep the position of each
** if player, create starting position
*/

int		check_point(t_data *data, int i, int *j)
{
	char	*map;
	int		w;
	int		k;

	k = -2;
	w = data->map.column;
	map = data->map.map;
	while (++k < 2)
		if (map[i - w + k] == ' ' || map[i + k] == ' ' ||
				map[i + w + k] == ' ')
			return (14);
	if (map[i] == '2')
	{
		data->spritepos[*j].x = (i % w) + 1.5;
		data->spritepos[*j].y = (i / w) + 1.5;
		*j = *j + 1;
	}
	if (ft_isinstring(map[i], "NWES"))
	{
		if (data->flag & PLAYER)
			return (21);
		player_vectors_init(data, map[i], i);
	}
	return (0);
}

/*
** check map
**
** check if map not too small
** create data for sprites
** check first and last column for wrong characters
** (already done for first and last line)
** check each point (closed map, sprite, player)
** verify there is a player
*/

int		check_map(t_data *data, int w, int h)
{
	int	i;
	int	error;
	int	j;

	i = w - 1;
	j = 0;
	if (h < 3 || w < 3)
		return (error = 15);
	if (!create_sprite_data(data, data->numsprite))
		return (error = 5);
	while (++i < w * (h - 1))
	{
		if (i % w == 0 || i % w == w - 1)
			if (data->map.map[i] != '1' && data->map.map[i] != ' ')
				return (error = 14);
		if (i % w != 0 && i % w != w - 1 &&
				ft_isinstring(data->map.map[i], "02NWES"))
			if ((error = check_point(data, i, &j)))
				return (error);
	}
	if (!(data->flag & PLAYER))
		return (error = 16);
	return (0);
}
