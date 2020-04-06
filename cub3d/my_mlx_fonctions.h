#ifndef MY_MLX_FONCTIONS_H
# define MY_MLX_FONCTIONS_H

typedef struct s_imagedata
{
	void	*img;
	char	*addr;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
}				t_imagedata;

/*
** my_mlx_color_fonctions
*/
int	create_color_int(int t, int r, int g, int b);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);

/*
** my_mlx_image_fonctions
*/

void	my_mlx_pixel_put(t_imagedata *img, int x, int y, int color);


#endif