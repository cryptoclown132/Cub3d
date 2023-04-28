# include "../inc/cub3d.h"

int32_t update_dot_position(t_hold *hold)
{
    mlx_put_image_to_window(hold->mlx, hold->mlx_win, hold->img_ptr, 0, 0);
    // draw_hc_map(hold);

// draw look
// draw_line(hold, hold->pos[0], hold->pos[1], (hold->look[0])*5, (hold->look[1])*5, 0x778899);

// int32_t i = 0;
    // draw_my_map2(hold);
    // while(i<HEIGHT)
    // {
    //     // raycast(hold);
    //     draw_line(hold, hold->wall_dist+100, i, hold->wall_dist, i, 0xff00);
    //     i++;
    // }
	// draw_looking_direction(hold);
	// put_info_on_window(hold);
    // hold->map_pos[0] = 0;
    // hold->map_pos[1] = 0;
    mlx_put_image_to_window(hold->mlx, hold->mlx_win, hold->player_img_ptr, hold->pos[0]-10, hold->pos[1]-10);
    mlx_do_sync(hold->mlx);
    return (0);
}

float pi_val(int32_t keycode, char *sin_or_cos)
{
    if (ft_strncmp(sin_or_cos, "sin", 3) == 0)
    {
        if (keycode == A)
            return (0.5 * M_PI);
        if (keycode == D)
            return (1.5 * M_PI);
        if (keycode == S)
            return (M_PI);
    }
    else if (ft_strncmp(sin_or_cos, "cos", 3) == 0)
    {
        if (keycode == A)
            return (0.5 * M_PI);
        if (keycode == D)
            return (2.5 * M_PI);
        if (keycode == S)
            return (3 * M_PI);
    }
    return (0);
}

/* function calculates based on the keyhook_events, new position of the player */
void calc_new_coordinate(t_hold *hold, int32_t keycode)
{
    if (keycode == W)
    {
        if (hold->cub->map[(int)(hold->pos[1] + (0.2 * hold->diry))][(int)hold->pos[0]] != '1')
            hold->pos[1] = hold->pos[1] + (0.2 * hold->diry);
        if (hold->cub->map[(int)hold->pos[1]][(int)(hold->pos[0] + (0.2 * hold->dirx))] != '1')
            hold->pos[0] = hold->pos[0] + (0.2 * hold->dirx);
    }
    else if (keycode == S)
    {
		if (hold->cub->map[(int)(hold->pos[1] - (0.2 * hold->diry))][(int)hold->pos[0]] != '1')
            hold->pos[1] = hold->pos[1] - (0.2 * hold->diry);
        if (hold->cub->map[(int)hold->pos[1]][(int)(hold->pos[0] - (0.2 * hold->dirx))] != '1')
            hold->pos[0] = hold->pos[0] - (0.2 * hold->dirx);
    }
    else if ( keycode == A)
    {
		if (hold->cub->map[(int)(hold->pos[1] - (0.2 * hold->plane[1]))][(int)hold->pos[0]] != '1')
            hold->pos[1] = hold->pos[1] - (0.2 * hold->plane[1]);
        if (hold->cub->map[(int)hold->pos[1]][(int)(hold->pos[0] - (0.2 * hold->plane[0]))] != '1')
            hold->pos[0] = hold->pos[0] - (0.2 * hold->plane[0]);
	}
    else if (keycode == D)
    {
		if (hold->cub->map[(int)(hold->pos[1] + (0.2 * hold->plane[1]))][(int)hold->pos[0]] != '1')
            hold->pos[1] = hold->pos[1] + (0.2 * hold->plane[1]);
        if (hold->cub->map[(int)hold->pos[1]][(int)(hold->pos[0] + (0.2 * hold->plane[0]))] != '1')
            hold->pos[0] = hold->pos[0] + (0.2 * hold->plane[0]);
	}
}

/* function calculates the new looking_direction based on the updated x and y values */
void calc_new_look_dir(t_hold *hold, int32_t keycode)
{

	//has to be changed
	float prev_dirx = hold->dirx;
    float prev_plane = hold->plane[0];
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
    hold->go = false;
    if (keycode == ESCAPE)
        exit(0);
    if (keycode == A || keycode == W || keycode == S || keycode == D)
        calc_new_coordinate(hold, keycode);
    if (keycode == LEFT || keycode == RIGHT)
        calc_new_look_dir(hold, keycode);
    put_image(hold);
    // // mlx_destroy_image(hold->mlx, hold->cub->img->img);
    // mlx_clear_window(hold->mlx, hold->mlx_win);

    // // image_init(hold);
    // put_image(hold);
    return (0);
}