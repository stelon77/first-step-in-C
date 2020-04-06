/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essai_minilib.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:07:19 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/03/08 18:07:24 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct 	s_parametres
{
	void* mlx;
	void* win;
	int	x;
	int	y;
}				t_parametres;

int deal_key(int key, void *param)
{
	t_parametres *essai;
	int i = 0;
	int j;

	essai = param;
	printf("essai->x =%d\n", essai->x);

	printf("le numero de touche est %d\n", key);

	if (key == 53)//touche escape
		exit(0);
	if (key == 126)
		essai->y--;
	if (key == 125)
		essai->y++;
	if (key == 124)
		essai->x++;
	if (key == 123)
		essai->x--;
	while (i++ <= 250)
	{
		j = 0;
		while (j < 250)
		{
			mlx_pixel_put(essai->mlx, essai->win, i, j, 0x8FF00FF);
			j++;
		}

	}
	return(0);
}

void init_param(t_parametres *param, void *mlx, void *win)
{
	param->mlx = mlx;
	param->win = win;
	param->x = 200;
	param->y = 200;
}

int quit(void )
{
	exit(EXIT_SUCCESS);
	return (0);
}

int main()
{
	t_parametres parametres;
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 250, 250, "clem et simon sont mes preferes");
	init_param(&parametres, mlx_ptr, win_ptr);
	mlx_pixel_put(mlx_ptr, win_ptr, parametres.x, parametres.y, 0xFFFFFFF);

	mlx_hook(win_ptr, 17, 0, quit, (void*)0);
	mlx_key_hook(win_ptr, deal_key, (void *)&parametres);
	mlx_loop(mlx_ptr);
}
