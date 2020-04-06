/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_image_fonctions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:26:38 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/03/14 19:51:01 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_imagedata *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + ((y * img->line_length) + (x * (img->bit_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

int		my_texcolor_extractor(t_imagedata *img, int x, int y)
{
	int color;
	char *dst;

	dst = img->addr + ((y * img->line_length) + (x * (img->bit_per_pixel / 8)));
	color = *(unsigned int *)dst;
	return (color);
}