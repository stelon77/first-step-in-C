/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 21:57:29 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/02/13 08:55:34 by lcoiffie         ###   ########.fr       */
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
	free(str);
	str = NULL;
}

static int	put_color_ceiling(t_data *data, char *r, char *g, char *b)
{
	int	i;

	i = -1;
	while (r[++i])
		if (!ft_isdigit(r[i]))
			return (9);
	if (ft_atoi(r) > 255)
		return (9);
	data->ceiling.red = ft_atoi(r);
	i = -1;
	while (g[++i])
		if (!ft_isdigit(g[i]))
			return (9);
	if (ft_atoi(g) > 255)
		return (9);
	data->ceiling.green = ft_atoi(g);
	i = -1;
	while (b[++i])
		if (!ft_isdigit(b[i]))
			return (9);
	if (ft_atoi(b) > 255)
		return (9);
	data->ceiling.blue = ft_atoi(b);
	return (0);
}

static int	put_color_floor(t_data *data, char *r, char *g, char *b)
{
	int	i;

	i = -1;
	while (r[++i])
		if (!ft_isdigit(r[i]))
			return (9);
	if (ft_atoi(r) > 255)
		return (9);
	data->floor.red = ft_atoi(r);
	i = -1;
	while (g[++i])
		if (!ft_isdigit(g[i]))
			return (9);
	if (ft_atoi(g) > 255)
		return (9);
	data->floor.green = ft_atoi(g);
	i = -1;
	while (b[++i])
		if (!ft_isdigit(b[i]))
			return (9);
	if (ft_atoi(b) > 255)
		return (9);
	data->floor.blue = ft_atoi(b);
	return (0);
}

int			ceiling_data(char *line, t_data *data)
{
	char	**str;
	int		error;
	char	*colors;
	char	**rgb;

	error = 0;
	if (data->flag & C)
		return (13);
	if (!(str = ft_split(line, 32)))
		return (error = 5);
	if (ft_strcmp(str[0], "C"))
		return (error = 9);
	if (!str[1] || str[2])
		return (error = 9);
	colors = str[1];
	if (!(rgb = ft_split(colors, ',')))
		return (error = 5);
	if (!rgb[1] || !rgb[2] || rgb[3])
		return (error = 9);
	error = put_color_ceiling(data, rgb[0], rgb[1], rgb[2]);
	freetab(rgb);
	freetab(str);
	data->flag |= C;
	return (error);
}

int			floor_data(char *line, t_data *data)
{
	char	**str;
	int		error;
	char	*colors;
	char	**rgb;

	error = 0;
	if (data->flag & F)
		return (13);
	if (!(str = ft_split(line, 32)))
		return (error = 5);
	if (ft_strcmp(str[0], "F"))
		return (error = 9);
	if (!str[1] || str[2])
		return (error = 9);
	colors = str[1];
	if (!(rgb = ft_split(colors, ',')))
		return (error = 5);
	if (!rgb[1] || !rgb[2] || rgb[3])
		return (error = 9);
	error = put_color_floor(data, rgb[0], rgb[1], rgb[2]);
	freetab(rgb);
	freetab(str);
	data->flag |= F;
	return (error);
}
