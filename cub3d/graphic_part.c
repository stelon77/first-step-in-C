/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:07:53 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/03/08 18:07:53 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void opening(t_data *data)
{
    data->time = 0;
    data->oldtime = 0;
}
*/

//calcul des variables pour chaque colonne de l'ecran
void variable_value(t_data *data, int x)
{
    data->camerax = ((2 * x) / ((double)data->screen.x)) - 1;
    data->raydir.x = data->dir.x + (data->plane.x * data->camerax);
    data->raydir.y = data->dir.y + (data->plane.y * data->camerax);
    data->mapx = (int)data->pos.x;
    data->mapy = (int)data->pos.y;
    if (data->raydir.x == 0)
    {
        data->deltadist.x = 1;
        data->deltadist.y = 0;
    }
    else if (data->raydir.y == 0)
    {
        data->deltadist.x = 0;
        data->deltadist.y = 1;
    }
    else
    {
        data->deltadist.x = fabs(1 / data->raydir.x);
        data->deltadist.y = fabs(1 / data->raydir.y);
    }
    //pas sur que ce soit lq bonne place
    //data->hit  = 0;
}

void  step_and_initial_sidedist(t_data *data)
{
    if (data->raydir.x < 0)
    {
        data->stepx = -1;
        data->sidedist.x = (data->pos.x - data->mapx) * data->deltadist.x;
    }
    else
    {
        data->stepx = 1;
        data->sidedist.x = (-data->pos.x + data->mapx + 1.0) * data->deltadist.x;
    }
    if (data->raydir.y < 0)
    {
        data->stepy = -1;
        data->sidedist.y = (data->pos.y - data->mapy) * data->deltadist.y;
    }
    else
    {
        data->stepy = 1;
        data->sidedist.y = (-data->pos.y + data->mapy + 1.0) * data->deltadist.y;
    }
}

void    perform_dda(t_data *data)
{
    //voir si pas mieux comme ca
    data->hit = 0;
    //
    while (data->hit == 0)
    {
        //jump to next map square
        if (data->sidedist.x < data->sidedist.y)
        {
            data->sidedist.x += data->deltadist.x;
            data->mapx += data->stepx;
            data->side = 0;
        }
        else
        {
            data->sidedist.y += data->deltadist.y;
            data->mapy += data->stepy;
            data->side = 1;
        }
        //on verifie si wall a ete touche
        if (data->map.map[(data->map.column * (data->mapy - 1)) + data->mapx - 1] == '1')
            data->hit = 1;
    }
}

void    calculate_distance(t_data *data)
{
    if (data->side ==0)
        data->perpwalldist = ((data->mapx - data->pos.x + ((1 - data->stepx) / 2) ) / data->raydir.x);
    else
        data->perpwalldist = ((data->mapy - data->pos.y + ((1 - data->stepy) / 2) ) / data->raydir.y);
}

void    calculate_column(t_data *data)
{
    //hauteur de la ligne a afficher
    int h;
    int lineh;

    h = data->screen.y;
    lineh = (int)(h / data->perpwalldist);
    data->lineheight = lineh;
    data->drawstart = (h-lineh)/2;
    if (data->drawstart < 0)
        data->drawstart = 0;
    data->drawend = (h+lineh)/2;
    if (data->drawend >= h)
        data->drawend = h - 1;
}

void    calculate_wallx_and_x_text(t_data *data)
{
    if (data->side == 0)
        data->wallx = data->pos.y + (data->perpwalldist * data->raydir.y);
    else
    {
        data->wallx = data->pos.x + (data->perpwalldist * data->raydir.x);
    }
    data->wallx -= floor(data->wallx);
    data->texx = (int)(data->wallx * (double)TEXWIDTH);
    if (data->side == 0 && data->raydir.x < 0)
        data->texx = TEXWIDTH - data->texx - 1;
    if (data->side == 1 && data->raydir.y > 0)
        data->texx = TEXWIDTH - data->texx - 1;
}

int find_textel_color_and_put(t_data *data, int x, t_imagedata *img)
{
    int h;
    int color;
    int y;


    h = data->screen.y;
    data->step = 1.0 * TEXHEIGHT / data->lineheight;
    data->texpos = (data->drawstart - (h / 2) + data->lineheight / 2) * data->step;
    y = data->drawstart;
    while (y < data->drawend)
    {
        data->texy = (int)data->texpos & (TEXHEIGHT - 1);
        data->texpos += data->step;
        color = my_texcolor_extractor(&data->currenttex, data->texx, data->texy);
        my_mlx_pixel_put(img, x, y, color);
        y++;
    }
    //set buffer for spritecasting
    data->zbuffer[x] = data->perpwalldist;
    return (y);
}


void    wall_color(t_data *data)
{
    if (data->side == 1 & data->stepy == 1)
        data->wallcolor = 0xFFFFFFF;//sud
    if (data->side == 1 & data->stepy == -1)
        data->wallcolor = 0xFFFFFFF;//nord
    if (data->side == 0 & data->stepx == 1)
        data->wallcolor = 0xFFFFFFF;//est
    if (data->side == 0 & data->stepx == -1)
        data->wallcolor = 5526612;//ouest
}

void    wall_color_tex(t_data *data)
{
    if (data->side == 1 & data->stepy == 1)
        data->currenttex = data->texsouth;//sud
    if (data->side == 1 & data->stepy == -1)
        data->currenttex = data->texnorth;//nord
    if (data->side == 0 & data->stepx == 1)
        data->currenttex = data->texeast;//est
    if (data->side == 0 & data->stepx == -1)
        data->currenttex = data->texwest;//ouest
}

//gestion du temps ???
//il n'y a plus qu'a dessiner ligne verticale et le faire pour
//tous les x

//maintenant gestion des mouvements

// int deal_key(int key, void *param, t_data *data)
// {
// 	t_data *new;

//     new = param;
//     new->movespeed = data->movespeed;
//     new->rotspeed = ROTSPEED;

//     if (key == 53)//touche escape
//         //procedure exit

//         //126 : fleche haut
//         //125 : fleche bas
//         // 13 : touche w
//         // 0 : touche a
//         //1 touche s
//         //2 touche d
//         exit (0);
//     return (0);
// }







void    petitmain(t_data *data)
{
    int x;//la colonne de l'ecran

    x = 0;
    while (x < data->screen.x)
    {
        variable_value(data, x);
    }
}