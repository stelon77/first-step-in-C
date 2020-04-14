/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 01:20:26 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/13 20:03:35 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			set_in_char(unsigned char *start, int n)
{
	start[0] = (unsigned char)(n);
	start[1] = (unsigned char)(n >> 8);
	start[2] = (unsigned char)(n >> 16);
	start[4] = (unsigned char)(n >> 24);
}

unsigned char	*put_bgr(t_data *data, int x, int y, unsigned char *bgr)
{
	unsigned int	color;

	color = my_color_extractor(&data->img, x, y);
	bgr[0] = get_b(color);
	bgr[1] = get_g(color);
	bgr[2] = get_r(color);
	return (bgr);
}

void			create_file_header(t_data *data, int pad, unsigned char *header)
{
	int				file_size;
	int				i;

	i = -1;
	while (++i < 14)
		header[i] = 0;
	file_size = 54 + ((3 * (int)data->screen.x + pad) * (int)data->screen.y);
	header[0] = 'B';
	header[1] = 'M';
	set_in_char(&header[2], file_size);
	set_in_char(&header[10], 54);
}

void			create_img_header(int h, int w, int pad, unsigned char *header)
{
	int				i;

	i = -1;
	while (++i < 40)
		header[i] = 0;
	set_in_char(header, 40);
	set_in_char(&header[4], w);
	set_in_char(&header[8], h);
	header[12] = 1;
	header[14] = 24;
	set_in_char(&header[20], ((3 * w) + pad) * h);
}
