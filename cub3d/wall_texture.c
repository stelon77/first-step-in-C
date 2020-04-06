/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 22:11:13 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/03/20 01:28:06 by lcoiffie         ###   ########.fr       */
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

int			texture_no_data(char *line, t_data *data)
{
	char	**str;
	int		error;

	error = 0;
	if (data->flag & NO)
		return (error = 13);
	if (!(str = ft_split(line, 32)))
		return (error = 5);
	if (ft_strcmp(str[0], "NO"))
		return (error = 8);
	if (!str[1] || str[2])
		return (error = 8);
	data->north = ft_strdup(str[1]);
	freetab(str);
	data->flag |= NO;
	return (error);
}

int			texture_so_data(char *line, t_data *data)
{
	char	**str;
	int		error;

	error = 0;
	if (data->flag & SO)
		return (error = 13);
	if (!(str = ft_split(line, 32)))
		return (error = 5);
	if (ft_strcmp(str[0], "SO"))
		return (error = 8);
	if (!str[1] || str[2])
		return (error = 8);
	data->south = ft_strdup(str[1]);
	freetab(str);
	data->flag |= SO;
	return (error);
}

int			texture_we_data(char *line, t_data *data)
{
	char	**str;
	int		error;

	error = 0;
	if (data->flag & WE)
		return (error = 13);
	if (!(str = ft_split(line, 32)))
		return (error = 5);
	if (ft_strcmp(str[0], "WE"))
		return (error = 8);
	if (!str[1] || str[2])
		return (error = 8);
	data->west = ft_strdup(str[1]);
	freetab(str);
	data->flag |= WE;
	return (error);
}

int			texture_ea_data(char *line, t_data *data)
{
	char	**str;
	int		error;

	error = 0;
	if (data->flag & EA)
		return (error = 13);
	if (!(str = ft_split(line, 32)))
		return (error = 5);
	if (ft_strcmp(str[0], "EA"))
		return (error = 8);
	if (!str[1] || str[2])
		return (error = 8);
	data->east = ft_strdup(str[1]);
	freetab(str);
	data->flag |= EA;
	return (error);
}
