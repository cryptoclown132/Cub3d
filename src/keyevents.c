# include "../inc/cub3d.h"

/* function calculates based on the keyhook_events, new position of the player */
void calc_new_coordinate(t_hold *hold, int32_t keycode)
{
    if (keycode == W)
    {
        if (hold->map[(int)(hold->pos[1] + (SPEED * hold->diry))][(int)hold->pos[0]] != '1')
            hold->pos[1] = hold->pos[1] + (SPEED * hold->diry);
        if (hold->map[(int)hold->pos[1]][(int)(hold->pos[0] + (SPEED * hold->dirx))] != '1')
            hold->pos[0] = hold->pos[0] + (SPEED * hold->dirx);
    }
    else if (keycode == S)
    {
		if (hold->map[(int)(hold->pos[1] - (SPEED * hold->diry))][(int)hold->pos[0]] != '1')
            hold->pos[1] = hold->pos[1] - (SPEED * hold->diry);
        if (hold->map[(int)hold->pos[1]][(int)(hold->pos[0] - (SPEED * hold->dirx))] != '1')
            hold->pos[0] = hold->pos[0] - (SPEED * hold->dirx);
    }
    else if ( keycode == A)
    {
		if (hold->map[(int)(hold->pos[1] - (SPEED * hold->plane[1]))][(int)hold->pos[0]] != '1')
            hold->pos[1] = hold->pos[1] - (SPEED * hold->plane[1]);
        if (hold->map[(int)hold->pos[1]][(int)(hold->pos[0] - (SPEED * hold->plane[0]))] != '1')
            hold->pos[0] = hold->pos[0] - (SPEED * hold->plane[0]);
	}
    else if (keycode == D)
    {
		if (hold->map[(int)(hold->pos[1] + (SPEED * hold->plane[1]))][(int)hold->pos[0]] != '1')
            hold->pos[1] = hold->pos[1] + (SPEED * hold->plane[1]);
        if (hold->map[(int)hold->pos[1]][(int)(hold->pos[0] + (SPEED * hold->plane[0]))] != '1')
            hold->pos[0] = hold->pos[0] + (SPEED * hold->plane[0]);
	}
}

/* function calculates the new looking_direction based on the updated x and y values */
void calc_new_look_dir(t_hold *hold, int32_t keycode)
{
	double prev_dirx = hold->dirx;
    double prev_plane = hold->plane[0];
   
    if (keycode == LEFT)
    {
        hold->dirx = hold->dirx * cos(-ROTATION_ANGLE) - hold->diry * sin(-ROTATION_ANGLE);
        hold->diry = prev_dirx * sin(-ROTATION_ANGLE) + hold->diry * cos(-ROTATION_ANGLE);
        hold->plane[0] = hold->plane[0] * cos(-ROTATION_ANGLE) - hold->plane[1] * sin(-ROTATION_ANGLE);
        hold->plane[1] = prev_plane * sin(-ROTATION_ANGLE) + hold->plane[1] * cos(-ROTATION_ANGLE);
    }
    else if (keycode == RIGHT)
    {
        hold->dirx = hold->dirx * cos(ROTATION_ANGLE) - hold->diry * sin(ROTATION_ANGLE);
        hold->diry = prev_dirx * sin(ROTATION_ANGLE) + hold->diry * cos(ROTATION_ANGLE);
        hold->plane[0] = hold->plane[0] * cos(ROTATION_ANGLE) - hold->plane[1] * sin(ROTATION_ANGLE);
        hold->plane[1] = prev_plane * sin(ROTATION_ANGLE) + hold->plane[1] * cos(ROTATION_ANGLE);
    }
}



int32_t key_hook(int keycode, t_hold *hold)
{
    if (keycode == ESCAPE)
        close_and_free(hold);
    if (keycode == A || keycode == W || keycode == S || keycode == D)
        calc_new_coordinate(hold, keycode);
    if (keycode == LEFT || keycode == RIGHT)
        calc_new_look_dir(hold, keycode);
    mlx_clear_window(hold->mlx, hold->mlx_win);
    put_image(hold);
    return (0);
}