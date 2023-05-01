/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyevents.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:36:25 by jkroger           #+#    #+#             */
/*   Updated: 2023/05/01 20:26:03 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calc_new_move_2(t_hold *hold, int32_t keycode)
{
	if (keycode == A)
	{
		if (hold->map[(int)(hold->pos[1] - (SPEED * hold->plane[1]))] \
			[(int)hold->pos[0]] != '1')
			hold->pos[1] = hold->pos[1] - (SPEED * hold->plane[1]);
		if (hold->map[(int)hold->pos[1]] \
			[(int)(hold->pos[0] - (SPEED * hold->plane[0]))] != '1')
			hold->pos[0] = hold->pos[0] - (SPEED * hold->plane[0]);
	}
	else if (keycode == D)
	{	
		if (hold->map[(int)(hold->pos[1] + (SPEED * hold->plane[1]))] \
			[(int)hold->pos[0]] != '1')
			hold->pos[1] = hold->pos[1] + (SPEED * hold->plane[1]);
		if (hold->map[(int)hold->pos[1]] \
			[(int)(hold->pos[0] + (SPEED * hold->plane[0]))] != '1')
			hold->pos[0] = hold->pos[0] + (SPEED * hold->plane[0]);
	}
}

void	calc_new_move(t_hold *hold, int32_t keycode)
{
	if (keycode == W)
	{
		if (hold->map[(int)(hold->pos[1] + (SPEED * hold->diry))] \
			[(int)hold->pos[0]] != '1')
			hold->pos[1] = hold->pos[1] + (SPEED * hold->diry);
		if (hold->map[(int)hold->pos[1]] \
			[(int)(hold->pos[0] + (SPEED * hold->dirx))] != '1')
			hold->pos[0] = hold->pos[0] + (SPEED * hold->dirx);
	}
	else if (keycode == S)
	{
		if (hold->map[(int)(hold->pos[1] - (SPEED * hold->diry))] \
			[(int)hold->pos[0]] != '1')
			hold->pos[1] = hold->pos[1] - (SPEED * hold->diry);
		if (hold->map[(int)hold->pos[1]] \
			[(int)(hold->pos[0] - (SPEED * hold->dirx))] != '1')
			hold->pos[0] = hold->pos[0] - (SPEED * hold->dirx);
	}
	else if (keycode == A || keycode == D)
		calc_new_move_2(hold, keycode);
}

void	calc_new_dir_right(t_hold *hold, double prev_dirx, double prev_plane)
{
	hold->dirx = hold->dirx * cos(ROTATION_ANGLE) - hold->diry \
		* sin(ROTATION_ANGLE);
	hold->diry = prev_dirx * sin(ROTATION_ANGLE) + hold->diry \
		* cos(ROTATION_ANGLE);
	hold->plane[0] = hold->plane[0] * cos(ROTATION_ANGLE) - hold->plane[1] \
		* sin(ROTATION_ANGLE);
	hold->plane[1] = prev_plane * sin(ROTATION_ANGLE) + hold->plane[1] \
		* cos(ROTATION_ANGLE);
}

void	calc_new_dir(t_hold *hold, int32_t keycode)
{
	double	prev_dirx;
	double	prev_plane;

	prev_dirx = hold->dirx;
	prev_plane = hold->plane[0];
	if (keycode == LEFT)
	{
		hold->dirx = hold->dirx * cos(-ROTATION_ANGLE) - hold->diry \
			* sin(-ROTATION_ANGLE);
		hold->diry = prev_dirx * sin(-ROTATION_ANGLE) + hold->diry \
			* cos(-ROTATION_ANGLE);
		hold->plane[0] = hold->plane[0] * cos(-ROTATION_ANGLE) - hold->plane[1] \
			* sin(-ROTATION_ANGLE);
		hold->plane[1] = prev_plane * sin(-ROTATION_ANGLE) + hold->plane[1] \
			* cos(-ROTATION_ANGLE);
	}
	else if (keycode == RIGHT)
		calc_new_dir_right(hold, prev_dirx, prev_plane);
}

int32_t	key_hook(int keycode, t_hold *hold)
{
	if (keycode == ESCAPE)
		close_and_free(hold);
	if (keycode == A || keycode == W || keycode == S || keycode == D)
		calc_new_move(hold, keycode);
	if (keycode == LEFT || keycode == RIGHT)
		calc_new_dir(hold, keycode);
	mlx_clear_window(hold->mlx, hold->mlx_win);
	put_image(hold);
	return (0);
}
