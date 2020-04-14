/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:32:18 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/07 22:39:09 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** filling the final map
*/

static void	create_map2(char *new, int w, char *old)
{
	int	i;
	int	j;
	int	n;

	j = 0;
	i = 0;
	n = 0;
	while (old[i])
	{
		if (old[i] == 'a')
		{
			i++;
			j += w;
			n = 0;
		}
		new[j + n] = old[i];
		i++;
		n++;
	}
}

/*
** return 0 if error
**
** create the final map (number of column equal to the max number of column)
** allocate the right size
** initialize whith space then fill the map
*/

int			create_map(t_map *map, int w, int h)
{
	char	*old;
	int		i;

	old = map->map;
	if (!(map->map = (char *)malloc(sizeof(char) * ((w * h) + 1))))
		return (0);
	i = -1;
	while (++i < w * h)
		map->map[i] = ' ';
	map->map[i] = '\0';
	create_map2(map->map, w, old);
	free(old);
	old = NULL;
	return (1);
}

/*
** return errornumber, 0 if ok
** check empty line in map
** increase column nuber if line longer than the others
** join new map data, add a "a" at the end
*/

int			map_writing(char *line, t_data *data)
{
	int		i;
	char	*old;
	char	*new;

	old = data->map.map;
	i = ft_strlen(line);
	if (i == 0)
		return (19);
	if (i > data->map.column)
		data->map.column = i;
	if (!(new = ft_strjoin(line, "a")))
		return (5);
	if (!(data->map.map = ft_strjoin(old, new)))
		return (5);
	free(old);
	old = NULL;
	free(new);
	new = NULL;
	data->map.line += 1;
	return (0);
}

/*
** return errornumber, 0 if ok
**
** first check if all data flags up, put flag map_on on
** second check right characters in line 1
** third initialize column and line
** create first line of map and column counter
** at the end of the line, put "a" (separator for further steps)
*/

int			first_line_map(char *line, t_data *data)
{
	int	i;

	if (data->flag != 255)
		return (10);
	i = -1;
	data->flag |= MAP_ON;
	data->map.column = 0;
	data->map.line = 0;
	while (line[++i])
		if (line[i] != ' ' && line[i] != '1')
			return (14);
	data->map.column = i;
	if (!(data->map.map = ft_strjoin(line, "a")))
		return (5);
	data->map.line += 1;
	return (0);
}
