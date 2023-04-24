# include "../inc/cub3d.h"

int32_t update_dot_position(t_hold *hold)
{
    mlx_put_image_to_window(hold->mlx, hold->mlx_win, hold->img_ptr, 0, 0);
    // draw_hc_map(hold);

// draw look
// draw_line(hold, hold->pos[0], hold->pos[1], (hold->look[0])*5, (hold->look[1])*5, 0x778899);

int32_t i = 0;
    // draw_my_map2(hold);
    while(i<HEIGHT)
    {
        // raycast(hold);
        draw_line(hold, hold->wall_dist+100, i, hold->wall_dist, i, 0xff00);
        i++;
    }
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
    float store_x;
    float tmp[2];

    tmp[0] = hold->look[0] - hold->pos[0];
    tmp[1] = hold->pos[1] - hold->look[1];
    store_x = hold->pos[0];
    hold->pos[0] = hold->pos[0] + (hold->look[0] - hold->pos[0]) * cos(pi_val(keycode, "cos")) \
            + (hold->look[1] - hold->pos[1]) * sin(pi_val(keycode, "sin"));
    hold->pos[1] = hold->pos[1] + (hold->look[1] - hold->pos[1]) * cos(pi_val(keycode, "cos")) \
            - (hold->look[0] - store_x) * sin(pi_val(keycode, "sin"));
    hold->look[0] = hold->pos[0] + tmp[0];
    hold->look[1] = hold->pos[1] - tmp[1];
    hold->go = true;
}

/* function calculates the new looking_direction based on the updated x and y values */
void calc_new_look_dir(t_hold *hold, int32_t keycode)
{
    float store_x_look;

	store_x_look = hold->look[0];
    if (keycode == LEFT)
    {
        hold->look[0] = hold->pos[0] + (hold->look[0] - hold->pos[0]) * cos(hold->angle) \
                    + (hold->look[1] - hold->pos[1]) * sin(hold->angle);
        hold->look[1] =hold->pos[1] + (hold->look[1] - hold->pos[1]) * cos(hold->angle) \
                    - (store_x_look - hold->pos[0]) * sin(hold->angle);
    }
	else
	{
		hold->look[0] = hold->pos[0] + (hold->look[0] - hold->pos[0]) * cos(2*M_PI+hold->angle) \
                    + (hold->look[1] - hold->pos[1]) * sin(2*M_PI-hold->angle);
        hold->look[1] =hold->pos[1] + (hold->look[1] - hold->pos[1]) * cos(2*M_PI+hold->angle) \
                    - (store_x_look - hold->pos[0]) * sin(2*M_PI-hold->angle);
	}
    hold->go = false;
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
    return (0);
}