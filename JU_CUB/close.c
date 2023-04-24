/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:49:26 by jkroger           #+#    #+#             */
/*   Updated: 2023/04/18 13:22:10 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_and_free(t_cub *cub)
{
	int	i;

	if (cub->map)
	{
		i = -1;
		while (cub->map[++i])
			free(cub->map[i]);
		free(cub->map);
	}
	if (cub->ceiling)
		free(cub->ceiling);
	if (cub->floor)
		free(cub->floor);
	if (cub->path_west)
		free(cub->path_west);
	if (cub->path_east)
		free(cub->path_east);
	if (cub->path_south)
		free(cub->path_south);
	if (cub->path_north)
		free(cub->path_north);
	if (cub->file_name)
		free(cub->file_name);
}
