#include "cub3d.h"

int texture_creation(t_data *data)
{
	create_img_east(data);
	create_img_west(data);
	create_img_north(data);
	create_img_south(data);
	create_img_sprite(data);
	return (0);

}

int	create_img_east(t_data *data)
{
	int width;
	int height;

	width = TEXWIDTH;
	height = TEXHEIGHT;
	//if (!(data->texeast.img = mlx_new_image(data->mlx, TEXWIDTH, TEXHEIGHT)))
	//	return (17);
	if (!(data->texeast.img = mlx_xpm_file_to_image(data->mlx, data->east, &width, &height)))
		return (18);//error 18
	data->texeast.addr = mlx_get_data_addr(data->texeast.img, &data->texeast.bit_per_pixel, &data->texeast.line_length, &data->texeast.endian);
	return (0);
}

int	create_img_north(t_data *data)
{
	int width;
	int height;

	width = TEXWIDTH;
	height = TEXHEIGHT;
	//if (!(data->texnorth.img = mlx_new_image(data->mlx, TEXWIDTH, TEXHEIGHT)))
	//	return (17);
	if (!(data->texnorth.img = mlx_xpm_file_to_image(data->mlx, data->north, &width, &height)))
		return (18);//error 18
	data->texnorth.addr = mlx_get_data_addr(data->texnorth.img, &data->texnorth.bit_per_pixel, &data->texnorth.line_length, &data->texeast.endian);
	return (0);
}

int	create_img_west(t_data *data)
{
	int width;
	int height;

	width = TEXWIDTH;
	height = TEXHEIGHT;
	// if (!(data->texwest.img = mlx_new_image(data->mlx, TEXWIDTH, TEXHEIGHT)))
	// 	return (17);
	if (!(data->texwest.img = mlx_xpm_file_to_image(data->mlx, data->west, &width, &height)))
		return (18);//error 18
	data->texwest.addr = mlx_get_data_addr(data->texwest.img, &data->texwest.bit_per_pixel, &data->texwest.line_length, &data->texwest.endian);
	return (0);
}

int	create_img_south(t_data *data)
{
	int width;
	int height;

	width = TEXWIDTH;
	height = TEXHEIGHT;
	// if (!(data->texsouth.img = mlx_new_image(data->mlx, TEXWIDTH, TEXHEIGHT)))
	// 	return (17);
	if (!(data->texsouth.img = mlx_xpm_file_to_image(data->mlx, data->south, &width, &height)))
		return (18);//error 18
	data->texsouth.addr = mlx_get_data_addr(data->texsouth.img, &data->texsouth.bit_per_pixel, &data->texsouth.line_length, &data->texsouth.endian);
	//mlx_put_image_to_window(data->mlx, data->win, data->texsouth.img, 0, 0);

	return (0);
}

int	create_img_sprite(t_data *data)
{
	int width;
	int height;

	width = TEXWIDTH;
	height = TEXHEIGHT;
	if (!(data->texsprite.img = mlx_xpm_file_to_image(data->mlx, data->sprite, &width, &height)))
		return (18);//error 18
	data->texsprite.addr = mlx_get_data_addr(data->texsprite.img, &data->texsprite.bit_per_pixel, &data->texsprite.line_length, &data->texsprite.endian);
	//mlx_put_image_to_window(data->mlx, data->win, data->texsprite.img, 0, 0);
	return (0);
}
