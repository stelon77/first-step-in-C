/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 23:36:25 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/07 22:18:50 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_name(char *arg)
{
	int	n;

	n = ft_strlen(arg);
	if (n < 5)
		return (1);
	if (ft_strcmp(&arg[n - 4], ".cub"))
		return (1);
	return (0);
}

int	check_argument_error(int argc, char *argv[], t_data *data)
{
	int	errornbr;

	data->save = 0;
	errornbr = 0;
	if (argc < 2 || argc > 3)
		errornbr = 1;
	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "--save"))
			errornbr = 2;
		data->save = 1;
	}
	if (check_name(argv[1]) && errornbr == 0)
		errornbr = 3;
	if (errornbr)
		display_error(errornbr);
	return (errornbr);
}

/*
** data file .cub checking
** and creating data from it
** return 0 if ok
*/

int	check_file(int fd, t_data *data)
{
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (!(read_line(line, data, fd, ret)))
		{
			free(line);
			line = NULL;
			return (1);
		}
		free(line);
		line = NULL;
	}
	if (ret == -1)
		return (error_freestruct(data, 5, 1, line));
	free(line);
	line = NULL;
	if (!(data->flag & MAP_ON))
		error_freestruct_fd(data, fd, 20);
	return (0);
}
