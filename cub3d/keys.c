# include "cub3d.h"

int		hit_key(int	key, t_data *data)
{
	if (key == 53)//esc
		closing(data);
	if (key == 13)//w
		data->move.up = 1;
		//forward(data);
	if (key == 1)//s
		data->move.down = 1;
		//backward(data);
	if (key == 0)//a
		data->move.left = 1;
		//sideleft(data);
	if (key == 2)//d
		data->move.right = 1;
		//sideright(data);
	if (key == 123)
		data->move.rot_l = 1;
		//rotation_left(data);
	if (key == 124)
		data->move.rot_r = 1;
		//rotation_right(data);
	return (0);
}

int		release_key(int	key, t_data *data)
{
	if (key == 13)//w
		data->move.up = 0;
		//forward(data);
	if (key == 1)//s
		data->move.down = 0;
		//backward(data);
	if (key == 0)//a
		data->move.left = 0;
		//sideleft(data);
	if (key == 2)//d
		data->move.right = 0;
		//sideright(data);
	if (key == 123)
		data->move.rot_l = 0;
		//rotation_left(data);
	if (key == 124)
		data->move.rot_r = 0;
		//rotation_right(data);
	return (0);
}
