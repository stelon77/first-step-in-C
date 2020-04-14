/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 21:58:00 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/04/14 19:31:38 by lcoiffie         ###   ########.fr       */
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

int			sprite_texture_data(char *line, t_data *data)
{
	char	**str;
	int		error;

	error = 0;
	if (data->flag & S)
		return (error = 13);
	if (!(str = ft_split(line, 32)))
		return (error = 5);
	if (ft_strcmp(str[0], "S"))
		return (freetab_error(str, 8));
	if (!str[1] || str[2])
		return (freetab_error(str, 8));
	data->sprite = ft_strdup(str[1]);
	freetab(str);
	data->flag |= S;
	return (error);
}
