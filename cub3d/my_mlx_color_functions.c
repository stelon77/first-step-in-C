/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_color_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 18:18:54 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/03/30 15:15:58 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_color_int(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0x000000FF);
}


int	get_r(int trgb)
{
	return ((trgb >> 16) & 0x000000FF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0x000000FF);
}

int	get_b(int trgb)
{
	return (trgb & 0x000000FF);
}