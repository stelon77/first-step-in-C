/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 23:50:49 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/07 22:52:43 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** dispaching for data information except map
*/

static int	data_filling(char *line, t_data *data)
{
	if (line[0] == 'R')
		return (resolution_data(line, data));
	if (line[0] == 'N')
		return (texture_no_data(line, data));
	if (line[0] == 'S' && line[1] == 'O')
		return (texture_so_data(line, data));
	if (line[0] == 'W')
		return (texture_we_data(line, data));
	if (line[0] == 'E')
		return (texture_ea_data(line, data));
	if (line[0] == 'S')
		return (sprite_texture_data(line, data));
	if (line[0] == 'C')
		return (ceiling_data(line, data));
	if (line[0] == 'F')
		return (floor_data(line, data));
	return (0);
}

/*
** return errornumber, 0 if ok
** check characters in line
** check number of sprites of the map
** return of map_writing function
*/

static int	map_filling(char *line, t_data *data)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!(ft_isinstring(line[i], MAP)))
			return (11);
		if (line[i] == '2')
			data->numsprite++;
	}
	return (map_writing(line, data));
}

/*
** return errornumber, 0 if ok
** first check characters of the line
** second check empty line
** third check column number +/- increase it
** fourth add theb last line to the map
** fifth create the final map with right column number
** finally check map parameters
*/

static int	last_line_map(char *line, t_data *data)
{
	int		i;
	char	*old;

	i = -1;
	while (line[++i])
		if (!(ft_isinstring(line[i], " 1")))
			return (11);
	old = data->map.map;
	if (i == 0)
		return (19);
	if (i > data->map.column)
		data->map.column = i;
	if (!(data->map.map = ft_strjoin(old, line)))
		return (5);
	free(old);
	old = NULL;
	data->map.line += 1;
	if (!(create_map(&data->map, data->map.column, data->map.line)))
		return (5);
	return (check_map(data, data->map.column, data->map.line));
	return (0);
}

/*
** return 0 = error
**
** first let remove the spaces at the beginning and the end of line
** second search the flags for datas
** third first line of map gestion
** fourth next lines of map
** fifth last line of the map
** sixth empty lines gestion
** seventh free trimed line
** finally errors gestion
*/

int			read_line(char *line, t_data *data, int fd, int ret)
{
	char	*newline;
	int		errors;

	errors = 6;
	if (!(newline = ft_strtrim(line, " ")))
		error_freestruct_fd(data, fd, 5);
	if (ft_isinstring(newline[0], FLAG) && (!(data->flag & MAP_ON)))
		errors = data_filling(newline, data);
	else if (newline[0] == '1' && !(data->flag & MAP_ON) && ret)
		errors = first_line_map(line, data);
	else if ((data->flag & MAP_ON) && ret)
		errors = map_filling(line, data);
	else if ((data->flag & MAP_ON) && !ret)
		errors = last_line_map(line, data);
	else if (!(data->flag & MAP_ON) && ft_strlen(newline) == 0)
		errors = 0;
	free(newline);
	newline = NULL;
	if (errors)
		error_freestruct_fd(data, fd, errors);
	return (1);
}
