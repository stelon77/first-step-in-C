/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:32:18 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/03/23 00:20:39 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// char		*parsing_line(char *line)
// {
// 	char	*temp_line;
// 	int		i;
// 	int		count;

// 	i = -1;
// 	count = 0;
// 	while (line[++i])
// 		if (!(ft_isspace(line[i])))
// 			count++;
// 	if (!(temp_line = ft_calloc(count + 1, sizeof(char))))
// 		return (NULL);
// 	i = 0;
// 	count = 0;
// 	while (line[i])
// 	{
// 		if (!(ft_isspace(line[i])))
// 		{
// 			temp_line[count] = line[i];
// 			count++;
// 		}
// 		i++;
// 	}
// 	return (temp_line);
// }


// static int	testline(char *new, t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	while (new[++i])
// 	{
// 		if (!(ft_isinstring(new[i], "012NWES")))
// 			return (1);
// 		if (ft_isinstring(new[i], "NWES"))
// 		{
// 			if (data->flag & PLAYER)
// 				return (1);
// 			data->flag |= PLAYER;
// 			data->pos.x = i + 1;
// 			data->pos.y = data->map.line + 1;
// 			player_vectors_init(data, new[i]);
// 			new[i] = '0';//mise a zero de la case player
// 		}
// 	}
// 	return (0);
// }

int			create_map(t_map *map, int w, int h)// si erreur renvoie 0
{
	char	*old;
	int		i;
	int		j;
	int		n;

	old = map->map;
	printf("%s\n%d\n%d\n", map->map, w, h);
	if(!(map->map = (char *)malloc(sizeof(char) *((w * h) + 1))))
		return (0);
	i = -1;
	while (++i < w * h)
		map->map[i] = ' ';
	map->map[i] = '\0';
	j = 0;
	i = 0;
	n = 0;
	while(old[i])
	{
		if (old[i] == 'a')
		{
			i++;
			j += w;
			n = 0;
		}
		map->map[j + n] = old[i];
		i++;
		n++;
	}
	free(old);
	old = NULL;
	return (1);
}

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

int			first_line_map(char *line, t_data *data) //return 0 si pas d'erreur
{
	int	i;

	if (data->flag != 255) //toutes les donnees hors carte sont la
		return (10);
	//on remplit ligne 1 apres avoir initialise column et line et mis en route la map
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
	//ft_putstr_fd("on sort de la premiere ligne\npour l'instant les data sont : %s\n,taille x%d\n, taille y%d\n", 1);
	ft_printf("on sort de la premiere ligne\npour l'instant les data sont : %s\n,taille x%d\n, taille y%d\n", data->map.map, data->map.column, data->map.line);
	return (0);
}
