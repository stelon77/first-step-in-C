#include <mlx.h>
#include "my_mlx_fonctions.h"

void zouzou(t_imagedata *img)
{
	int j;
	int i = 20;

	while (i++ <= 650)
	{
		j = 100;
		while (j < 400)
		{
			my_mlx_pixel_put(img, i, j, 0x8FFFFFF);
			j++;
		}

	}
}

int	main(void)
{
	void *mlx;
	void *mlx_win;
	t_imagedata img;

	mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 750, 500, "Hello world!");
	img.img = mlx_new_image(mlx, 750, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bit_per_pixel, &img.line_length, &img.endian);
	zouzou(&img);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}

