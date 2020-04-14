/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 13:32:54 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/13 18:19:24 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	int		fd;
	t_data	data;

	if (check_argument_error(argc, argv, &data))
		return (0);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (display_error(4));
	initialize_struct(&data);
	if (check_file(fd, &data))
	{
		close(fd);
		return (EXIT_SUCCESS);
	}
	close(fd);
	if (data.save == 1)
		let_s_save(&data);
	let_s_play(&data);
	return (EXIT_SUCCESS);
}
