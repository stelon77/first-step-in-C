/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_s_play.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:06:05 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/03 13:02:22 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	closing(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img);
	free_struct(data);
	exit(EXIT_SUCCESS);

}

int	keyboard(int keycode, t_data *data)
{
	if (keycode == 53)//esc
		closing(data);
	if (keycode == 13)//w
		forward(data);
	if (keycode == 1)//s
		backward(data);
	if (keycode == 0)//a
		sideleft(data);
	if (keycode == 2)//d
		sideright(data);
	if (keycode == 123)
		rotation_left(data);
	if (keycode == 124)
		rotation_right(data);

	printf(" voici les donnees \nposition x = %f, y = %f, et direction x = %f, y = %f\n", data->pos.x, data->pos.y, data->dir.x, data->dir.y);
	return (0);
}

int	zobizobi(t_imagedata *img, t_data *data)
{
	int	x;
	int ceilingcolor;
	int floorcolor;
	int y;

	ceilingcolor = create_color_int(0, data->ceiling.red, data->ceiling.green, data->ceiling.blue);
	floorcolor = create_color_int(0, data->floor.red, data->floor.green, data->floor.blue);
	x = 0;
	while (x < data->screen.x)
	{
		variable_value(data, x);
		step_and_initial_sidedist(data);
		perform_dda(data);
		calculate_distance(data);
		calculate_column(data);
		wall_color_tex(data);
		wall_color(data);
		y = 0;
		while (y < data->screen.y)
		{
			if (y < data->drawstart)
				my_mlx_pixel_put(img, x, y, ceilingcolor);
			if (y >= data->drawstart && y< data->drawend)
			{
			 	calculate_wallx_and_x_text(data);
			 	y = find_textel_color_and_put(data, x, img);
			}
			if (y >= data->drawend)
				my_mlx_pixel_put(img, x, y, floorcolor);
			y++;
		}
		x++;
		sprite_drawing(data, img);
	}
	if (data->save == 1)
		ft_save(data);//il faut aussi penser erreurs +++
	return (0);
}

int	let_s_play(t_data *data)
{
	if(!(data->mlx = mlx_init()))
		return (17);//erreur 17
	if (!(data->win = mlx_new_window(data->mlx, data->screen.x, data->screen.y, "cub3D")))
		return (17);
	texture_creation(data);
	if (!(data->img.img = mlx_new_image(data->mlx, data->screen.x, data->screen.y)))
		return (17);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bit_per_pixel, &data->img.line_length, &data->img.endian);
	zobizobi(&data->img, data);
	// if (data->save == 1)
	// 	ft_save(data);//il faut aussi penser erreurs +++

	//mlx_put_image_to_window(data->mlx, data->win, data->currenttex.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);

	mlx_hook(data->win, 2, 1L<<0, hit_key, data);//clavier enfonce
	//mlx_hook(data->win, 2, 1L<<0, keyboard, data);//clavier enfonce

	mlx_hook(data->win, 3, 1L<<1, release_key, data);//clavier relache
	mlx_hook(data->win, 17,1L<<2, closing, data);//bouton rouge
	mlx_loop_hook(data->mlx, let_s_move, data);
	mlx_loop(data->mlx);
	return (0);
}