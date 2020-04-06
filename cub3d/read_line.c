/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 23:50:49 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/03/22 15:56:01 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

//static int	map_filling(char *line, t_data *data)
int	map_filling(char *line, t_data *data)
{
	int	i;

	i = -1;
	// controle bon caracteres dans la ligne
	// recencesement des sprites
	while (line[++i])
	{
		if (!(ft_isinstring(line[i],MAP)))
			return (11);
		if (line[i] == '2')
			data->numsprite++;
	}
	ft_printf("la ligne est : %s\n", line);
	ft_printf("la map est  :%s\n", data->map.map);
	return (map_writing(line, data));
}

//static int	last_line_map(char *line, t_data *data) //renvoie 0 si ok
int	last_line_map(char *line, t_data *data) //renvoie 0 si ok
{
	int	i;
	char*	old;

	i = -1;
	while (line[++i])
		if (!(ft_isinstring(line[i]," 1")))
			return (19);
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
	ft_printf("on sort de la derniere ligne\ncreation  de la nouvelle ligne\n");
	if (!(create_map(&data->map, data->map.column, data->map.line)))
		return (5);
	printf("%s\nla taille de la map est %zu et w x h est %d\n", data->map.map, ft_strlen(data->map.map), data->map.column * data->map.line);
	return (check_map(data, data->map.column, data->map.line));
	return (0);
}

int 		read_line(char *line, t_data *data, int fd, int ret)// si erreur retour 0
{
	char	*newline;
	int		errors;

	errors = 0;
//on trime les 1eres lignes
	if (!(newline  = ft_strtrim(line, " ")))
		error_freestruct_fd(data, fd, 5);
//gestion des caracteristiques
	if (ft_isinstring(newline[0], FLAG) && (!(data->flag & MAP_ON)))
		errors = data_filling(newline, data);
// //gestion  1ere ligne de la carte
	else if (newline[0] == '1' && !(data->flag & MAP_ON) && ret)
 		errors = first_line_map(line, data);
// gestion des autres lignes
	else if ((data->flag & MAP_ON) && ret)
		errors = map_filling(line, data);
// gestion derniere ligne carte
	else if ((data->flag & MAP_ON) && !ret)
		errors = last_line_map(line, data);
//gestion lignes vides
	else if (!(data->flag & MAP_ON) && ft_strlen(newline) == 0)
		errors = 0;
//gestion cas erreur fichier
	else
	{
		errors = 6;
	}
 	free(newline);
 	newline = NULL;
// // si erreurs
	if (errors)
 		error_freestruct_fd(data, fd, errors);
	return (1);
}
