/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 01:39:59 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/14 19:41:42 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	freetab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str[i]);
	str[i] = NULL;
	free(str);
	str = NULL;
}

int			freetab_error(char **str, int error)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str[i]);
	str[i] = NULL;
	free(str);
	str = NULL;
	return (error);
}

static int	put_res_height(t_data *data, char *y)
{
	int	i;

	i = 0;
	while (y[i])
	{
		if (!ft_isdigit(y[i]))
			return (7);
		i++;
	}
	data->screen.y = ft_atoi(y);
	if (data->screen.y == 0)
		return (7);
	if (data->screen.y > TAILLE_MAX_Y)
		data->screen.y = TAILLE_MAX_Y;
	return (0);
}

static int	put_res_width(t_data *data, char *x, char *y)
{
	int	i;

	i = 0;
	while (x[i])
	{
		if (!ft_isdigit(x[i]))
			return (7);
		i++;
	}
	data->screen.x = ft_atoi(x);
	if (data->screen.x == 0)
		return (7);
	if (data->screen.x > TAILLE_MAX_X)
		data->screen.x = TAILLE_MAX_X;
	return (put_res_height(data, y));
}

int			resolution_data(char *line, t_data *data)
{
	char	*x;
	char	*y;
	char	**str;
	int		error;

	error = 0;
	if (data->flag & R)
		return (error = 13);
	if (!(str = ft_split(line, 32)))
		return (error = 5);
	if (ft_strcmp(str[0], "R"))
		return (freetab_error(str, 7));
	if (!str[1] || !str[2] || str[3])
		return (freetab_error(str, 7));
	x = str[1];
	y = str[2];
	error = put_res_width(data, x, y);
	freetab(str);
	data->flag |= R;
	return (error);
}
