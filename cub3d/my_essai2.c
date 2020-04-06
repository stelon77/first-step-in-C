#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_vars
{
    void        *mlx;
    void        *win;
	int 		x;
	int			y;

}               t_vars;

int             close(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_pixel_put(vars->mlx, vars->win, vars->x, vars->y, 0xFFFFFFF);
		vars->x++;
		vars->y++;

	}


	return (0);
}

int				close2(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	printf("bouton exit appuye\n");
	exit (0);
}

int				close3(void)
{
	printf("entree souris\n");
	return (0);
}

int				close4(void)
{
	printf("sortie souris\n");
	return (0);
}

int             main(void)
{
    t_vars      vars;

	vars.x =100;
	vars.y = 100;
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 750, 750, "Hello world!");
    //mlx_key_hook(vars.win, close, &vars);
	//mlx_hook(vars.win, 2, 1L<<0, close, &vars);
	mlx_hook(vars.win, 17,1L<<2, close2, &vars);

	

    mlx_loop(vars.mlx);
}