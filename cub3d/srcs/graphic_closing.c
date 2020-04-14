/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_closing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:59:04 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/14 19:55:48 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	closing_error(t_data *data, int errornbr)
{
	display_error(errornbr);
	closing(data);
	return (0);
}

int	closing(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->texeast.img)
		mlx_destroy_image(data->mlx, data->texeast.img);
	if (data->texnorth.img)
		mlx_destroy_image(data->mlx, data->texnorth.img);
	if (data->texsouth.img)
		mlx_destroy_image(data->mlx, data->texsouth.img);
	if (data->texsprite.img)
		mlx_destroy_image(data->mlx, data->texsprite.img);
	if (data->texwest.img)
		mlx_destroy_image(data->mlx, data->texwest.img);
	free_struct(data);
	exit(EXIT_SUCCESS);
}
