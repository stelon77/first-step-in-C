/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_image2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 17:39:21 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/13 23:48:28 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture_creation(t_data *data)
{
	create_img_east(data);
	create_img_west(data);
	create_img_north(data);
	create_img_south(data);
	create_img_sprite(data);
	return (0);
}
