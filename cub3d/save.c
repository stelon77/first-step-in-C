#include "cub3d.h"

void			set_in_char(unsigned char *start, int n)
{
	start[0] = (unsigned char)(n);
	start[1] = (unsigned char)(n >> 8);
	start[2] = (unsigned char)(n >> 16);
	start[4] = (unsigned char)(n >> 24);
}

void			create_file_header(t_data *data, int pad, unsigned char *file_header)
{
	int				file_size;
	int				i;

	i = -1;
	while (++i < 14)
		file_header[i] = 0;
	file_size = 54 + ((3 * (int)data->screen.x + pad) * (int)data->screen.y);
	file_header[0] = 'B';
	file_header[1] = 'M';
	set_in_char(&file_header[2], file_size);
	set_in_char(&file_header[10], 54);
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
	set_in_char(&header[20], ((3 * w)+ pad) * h);
	printf("fini les headers");
}

int				init_save(t_data *data, t_save *save)
{
	save->h = (int)data->screen.y;
	save->w = (int)data->screen.x;
	save->pad = (4 - ((save->w * 3) % 4)) % 4;
	create_file_header(data, save->pad, save->file_header);
	create_img_header(save->h, save->w, save->pad, save->img_header);
	return (0);
}

int				write_header(t_save *save)
{
	if ((write(save->fd, save->file_header, 14)) < 0)
	{
		close(save->fd);
		return (23);
	}
	if ((write(save->fd, save->img_header, 40)) < 0)
	{
		close(save->fd);
		return (23);
	}
	return (0);
}

unsigned char	*put_bgr(t_data *data, int x, int y, unsigned char *bgr)
{
	int				color;

	color = my_texcolor_extractor(&data->img, x, y);
	bgr[0] = get_b(color);
	bgr[1] = get_g(color);
	bgr[2] = get_r(color);
	//printf("ligne %d, colonne %d, color %X b %d, g, %d, r %d\n", y, x, color, bgr[0], bgr[1], bgr[2]);

	return (bgr);

}

int				write_picture(t_save *save, t_data *data)
{
	int				column;
	int				line;
	unsigned char	bgr[3];

	line = save->h - 1;
	while (line >= 0)
	{

		column = 0;
		while (column < save->w)
		{
			if ((write(save->fd, put_bgr(data, column, line, bgr), 3)) < 0)
				return (23);
			// if (column % 100 == 0 && line % 100 == 0)
			//	printf("ligne %d, colonne %d, b %d, g, %d, r %d", line, column, bgr[0], bgr[1], bgr[2]);
			 column ++;
		}
		if (save->pad > 0)
			if ((write(save->fd, "\0\0\0", save->pad)) < 0)
				return (23);
		line--;
	}
	return(0);
}

int				ft_save(t_data *data)		//renvoie 22 si ouvertureko, 23 si ecriture ko
{
	t_save	save;
	int		error;

	init_save(data, &save);
	if ((save.fd = open(SAVE, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644)) < 0)
		return (error = 22);
	if ((error = write_header(&save)))
		return (error);
	if ((error = write_picture(&save, data)))
	{
		close(save.fd);
		return (error);
	}
	printf("sauvegarde effectuee");
	close(save.fd);
	data->save = 0;
	return (0);
}