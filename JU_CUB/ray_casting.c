/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:42:24 by jkroger           #+#    #+#             */
/*   Updated: 2023/04/24 16:03:49 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_casting(t_cub *cub)
{
	cub->line_height = (int)(HEIGHT / cub->perpWallDist);
	cub->tex_start = -cub->line_height / 2 + HEIGHT / 2;
	if (cub->tex_start < 0)
		cub->tex_start = 0;
	cub->tex_end = cub->line_height / 2 + HEIGHT / 2;
	if (cub->tex_end >= HEIGHT)
		cub->tex_end = HEIGHT - 1;
}
