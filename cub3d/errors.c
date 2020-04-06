/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:41:00 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/04 18:13:52 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		error_freestruct(t_data *data, int errornb, int ret, char *line)
{
	free_struct(data);
	display_error(errornb);
	if (line)
	{
		free(line);
		line = NULL;
	}
	return (ret);
}

void	error_freestruct_fd(t_data *data, int fd, int errornb)
{
	display_error(errornb);
	free_struct(data);
	close(fd);
	exit(EXIT_FAILURE);
}

int		display_error(int errornbr)
{
	ft_putstr_fd("Error\n", 1);
	if (errornbr == 1)
		ft_putstr_fd("1 or 2 arguments only, is it so difficult ?\n", 1);
	if (errornbr == 2)
		ft_putstr_fd("Should use \"--save\" as second argument, OK ?\n", 1);
	if (errornbr == 3)
		ft_putstr_fd("You clever man, this is not a *.cub file\n", 1);
	if (errornbr == 4)
		ft_putstr_fd("Big problem : Could not open *.cub file\n", 1);
	if (errornbr == 5)
		ft_putstr_fd("Malloc error don't pump on memory\n", 1);
	if (errornbr == 6)
		ft_putstr_fd("Input Error --> Eh man, put a valid datafile !\n", 1);
	if (errornbr == 7)
		ft_putstr_fd("Input Error --> resolution, guys, resolution !\n", 1);
	if (errornbr == 8)
		ft_putstr_fd("Input Error --> OMG, texture data aren't good !\n", 1);
	if (errornbr == 9)
		ft_putstr_fd("Input Error --> floor or ceiling are important too\n", 1);
	if (errornbr == 10)
		ft_putstr_fd("Input Error --> F..k !! where are the missing datas\n", 1);
	if (errornbr == 11)
		ft_putstr_fd("Input Error --> Oh NO !! wrong character in map\n", 1);
	if (errornbr == 12)
		ft_putstr_fd("Input Error --> Listen... they said only one player\n", 1);
	if (errornbr == 13)
		ft_putstr_fd("Input Error --> again and over again, you put redondant data\n", 1);
	if (errornbr == 14)
		ft_putstr_fd("Input Error --> Pfouuu, not a closed map\n", 1);
	if (errornbr == 15)
		ft_putstr_fd("Input Error --> I think we don't have map data\n", 1);
	if (errornbr == 16)
		ft_putstr_fd("Input Error --> Come on, we need a  player in map\n", 1);
	if (errornbr == 17)
		ft_putstr_fd("graphic initialization failed\n", 1);
	if (errornbr == 18)
		ft_putstr_fd("error with texture, check the path\n", 1);
	if (errornbr == 19)
		ft_putstr_fd("input error->empty line in map\n", 1);
	if (errornbr == 20)
		ft_putstr_fd("input error->where is the map ?\n", 1);
	if (errornbr == 21)
		ft_putstr_fd("Input Error ->only one player, please\n", 1);
	if (errornbr == 22)
		ft_putstr_fd("aaaargh ! can't open save file\n", 1);
	if (errornbr == 23)
		ft_putstr_fd("Hey, I can't write in save file\n", 1);
	return (0);
}

