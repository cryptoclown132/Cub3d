/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:19:53 by jkroger           #+#    #+#             */
/*   Updated: 2023/05/01 19:32:14 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	player_dir_south(t_hold *hold)
{
	hold->dirx = 0;
	hold->diry = 1;
	hold->plane[0] = -0.9;
	hold->plane[1] = 0;
}

void	player_dir_north(t_hold *hold)
{
	hold->dirx = 0;
	hold->diry = -1;
	hold->plane[0] = 0.9;
	hold->plane[1] = 0;
}

void	player_dir_east(t_hold *hold)
{
	hold->dirx = 1;
	hold->diry = 0;
	hold->plane[0] = 0;
	hold->plane[1] = 0.9;
}

void	player_dir_west(t_hold *hold)
{
	hold->dirx = -1;
	hold->diry = 0;
	hold->plane[0] = 0;
	hold->plane[1] = -0.9;
}

void	player_dir(t_hold *hold, int j, int i, char player)
{
	hold->map_pos[0] = j;
	hold->map_pos[1] = i;
	hold->pos[0] = j + 0.5;
	hold->look[0] = i + 0.5;
	hold->pos[1] = i + 0.5;
	hold->look[1] = j + 0.5 - LINE_LEN;
	if (player == 'S')
		player_dir_south(hold);
	else if (player == 'N')
		player_dir_north(hold);
	else if (player == 'E')
		player_dir_east(hold);
	else if (player == 'W')
		player_dir_west(hold);
}
