#include "cub3d.h"

static void	sprite_sorting(int *order, double *dist, int amount)
{
	int		i;
	int		j;
	double	tempdist;
	int		temporder;

	i = 0;
	while (i < amount - 1)
	{
		j = 1;
		while ((i + j) < amount)
		{
			if (dist[i] < dist[i + j])
			{
				tempdist = dist[i];
				dist[i] = dist[i + j];
				dist[i+ j] = tempdist;
				temporder = order[i];
				order[i] = order[i + j];
				order[i + j] = temporder;
			}
			j++;
		}
		i++;
	}
}

void		sort_sprite(t_data *data)
{
	int 	i;
	double	x;
	double	y;

	i = 0;
	while (i < data->numsprite)
	{
		x = data->pos.x - data->spritepos[i].x;
		y = data->pos.y - data->spritepos[i].y;
		data->spriteorder[i] = i;
		data->spritedistance[i] = (x * x) + (y * y);
		i++;
	}
	sprite_sorting(data->spriteorder, data->spritedistance, data->numsprite);
}

//translate sprite position a la camera
//transform sprite via inverse camera matrix
void		transform_sprite(t_data *data, int i)
{
	double	invdet;

	data->spritex = data->spritepos[data->spriteorder[i]].x - data->pos.x;
	data->spritey = data->spritepos[data->spriteorder[i]].y - data->pos.y;
	invdet = 1.0 / (data->plane.x * data->dir.y - data->dir.x * data->plane.y);
	data->transformx = invdet * (data->dir.y * data->spritex - data->dir.x * data->spritey);
	data->transformy = invdet * (-data->plane.y * data->spritex + data->plane.x * data->spritey);
	data->spritescreenx = (int)((data->screen.x / 2) * (1 + data->transformx / data->transformy));
}

void 		sprite_height_width(t_data *data)
{
	data->spriteheight =  abs((int)(data->screen.y / data->transformy));//nofisheyeeffect
	data->drawstarty = (data->screen.y - data->spriteheight) / 2;
	if (data->drawstarty < 0)
		data->drawstarty = 0;
	data->drawendy = (data->screen.y + data->spriteheight) / 2;
	if (data->drawendy >= data->screen.y)
		data->drawendy = data->screen.y - 1;
	//pas sur qu'il y a besoin des conditions pour le x
	data->spritewidth =  abs((int)(data->screen.y / data->transformy));//nofisheyeeffect
	data->drawstartx = data->spritescreenx - (data->spritewidth / 2);
	if (data->drawstartx < 0)
		data->drawstartx = 0;
	data->drawendx = data->spritescreenx + (data->spritewidth / 2);
	if (data->drawendx >= data->screen.x)
		data->drawendx = data->screen.x - 1;
}


// a diviser en 2 parties
void 		sprite_drawing_loop(t_data *data, t_imagedata *img)
{
	int	x;
	//int	d;
	int	y;
	int	color;
	int prop;
	int prop2;
	int propy;
	int propy2;

	prop = data->spritescreenx - (data->spritewidth / 2);
	prop2 = 256 * TEXWIDTH / data->spritewidth;
	propy = (data->screen.y - data->spriteheight)/2;
	propy2 = 256 * TEXHEIGHT / data->spriteheight;

	data->texx = 30;
	data->texy = 30;
	x = data->drawstartx;
	if (data->transformy > 0)
	{
	//printf("spritewidth = %d, spriteheight = %d\n", data->spritewidth, data->spriteheight);
		while (x < data->drawendx)
		{
			//data->texx = (int)(256 * (x - (data->spritescreenx - (data->spritewidth / 2))) * TEXWIDTH / data->spritewidth) / 256;
			//if (data->transformy > 0 && x > 0 && x < data->screen.x && data->transformy < data->zbuffer[x])
			if (data->transformy < data->zbuffer[x])
			{
		//
				//data->texx = (int)((x - prop) * prop2) / 256;
		//
				y = data->drawstarty;
				while (y < data->drawendy)
				{
					//d = y * 256 - data->screen.y * 128 + data->spriteheight * 128;
					//d = 256 * (y - propy);
					//data->texy = (d * TEXHEIGHT / data->spriteheight) / 256;
					//d = y - (int)data->screen.y + data->spriteheight;
					//data->texy = ((y - propy) * propy2) / 256;
					color = my_texcolor_extractor(&data->texsprite, data->texx, data->texy);
					if ((color & 0x00FFFFFF) != 0)
							my_mlx_pixel_put(img, x, y, color);
					y++;
				}
			}
			x++;
		}
	}
}


int	sprite_drawing(t_data *data, t_imagedata *img)
{
	int i;

	i = 0;
	sort_sprite(data);
	while (i < data->numsprite)
	{
		transform_sprite(data, i);
		sprite_height_width(data);
		sprite_drawing_loop(data, img);
		i++;
	}
	//i = img->bit_per_pixel;
	return (0);
}
