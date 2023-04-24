# include "../inc/cub3d.h"
# include "../libft/libft.h"

int32_t	destroy_window(t_hold *hold)
{
	mlx_destroy_window(hold->mlx, hold->mlx_win);
	exit(0);
}

// void	my_mlx_pixel_put(t_hold *hold, int x, int y, int color)
// {
// 	char	*dst;

// 	if (x < WIDHT && y < HEIGHT && x > 0 && y > 0)
// 	{
// 		dst = hold->data_addr + (y * hold->size_line + x * (hold->bits_per_pixel / 8));
// 		*(unsigned int *)dst = color;
// 	}
// }

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


void init_cub(t_hold *hold, char **argv)
{
    hold->cub = malloc(sizeof(t_cub));
    hold->cub->img = NULL;
    hold->cub->img_2 = NULL;
    hold->cub->img_north = NULL;
    hold->cub->img_east = NULL;
    hold->cub->img_south = NULL;
    hold->cub->img_west = NULL;
    hold->cub->map = NULL;
    hold->cub->floor = NULL;
    hold->cub->path_north = NULL;
    hold->cub->path_east = NULL;
    hold->cub->path_south = NULL;
    hold->cub->path_west = NULL;
    hold->cub->map_rows = 1;
    hold->cub->map_columns = 0;
    hold->cub->player_dir = '\0';
	hold->cub->file_name = ft_strdup(argv[1]);
//wbu mlx and mlx_win
}

// gpt putline
void draw_line(t_hold *hold, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx, sy;
    if (x0 < x1) 
        sx = 1;
    else 
        sx = -1;
    if (y0 < y1)
        sy = 1;
    else
        sy = -1;
    int err = dx - dy;
    while (x0 != x1 || y0 != y1)
    {
        mlx_pixel_put(hold->mlx, hold->mlx_win, x0, y0, color);
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void check_4_general_errors(char **argv, int32_t argc)
{
    if (argc != 2)
		ft_error("Number of arguments must be 2!");
    check_file(argv[1]);
}

void init_minimap(t_hold *hold)
{
    hold->minimap = malloc(sizeof(t_minimap));

}

void init_structs(t_hold *hold, char **argv)
{
    hold->mlx = NULL;
    hold->pos[0] = 100;
    hold->pos[1] = 100;
    init_cub(hold, argv);
    init_minimap(hold);
}

void initialize_mlx(t_hold *hold)
{
    hold->mlx = mlx_init();
    if (!hold->mlx)
		ft_error("Failed to malloc for struct!");
    hold->mlx_win = mlx_new_window(hold->mlx, WIDHT, HEIGHT, WINDOW_NAME);
    if (!hold->mlx_win)
	{
		free(hold->mlx_win);
        // later free complete hold
		ft_error("Failed to open mlx window!");
	}
    hold->bits_per_pixel = 8;
    hold->size_line = 0;
    hold->endian = 0;
    hold->player_img_ptr = mlx_xpm_file_to_image(hold->mlx, "invader.xpm", (int*)&hold->pos[0], (int*)&hold->pos[1]);
    hold->img_ptr = mlx_new_image(hold->mlx, WIDHT, HEIGHT);
    hold->data_addr = mlx_get_data_addr(hold->img_ptr, &hold->bits_per_pixel, &hold->size_line, &hold->endian);
    hold->pos[0] = PLAYER_POSITION_X;
    hold->pos[1] = PLAYER_POSITION_Y;
    hold->look[0] = hold->pos[0];
    hold->look[1] = hold->pos[1] - LINE_LEN;
    hold->angle = ROTATION_ANGLE;
    hold->go = false;
}

// bool hit_wall(t_hold *hold, int32_t curr_x, int32_t curr_y)
// {
//     int round_x;
//     int round_y;

//     round_x = curr_x%TILE_SIZE;
//     round_y = curr_y%TILE_SIZE;
//     if (round_x == 0 || round_y == 0)
//     {
//         if (hold->cub->map[round_x][round_y] == 1)
//         {
//             hold->wall[0] = curr_x;
//             hold->wall[1] = curr_y;
//             return (true);
//         }
//     }
//     return (false);
// }

// void next_step(float tmp_pos[1][2], float tmp_look[1][2])
// {
//     float store_x;
//     float tmp[2];

//     tmp[0] = *tmp_look[0] - *tmp_pos[0];
//     tmp[1] = *tmp_pos[1] - *tmp_look[1];
//     store_x = *tmp_pos[0];
//     *tmp_pos[0] = *tmp_pos[0] + (*tmp_look[0] - *tmp_pos[0]);
//     *tmp_pos[1] = *tmp_pos[1] + (*tmp_look[1] - *tmp_pos[1]);
//     *tmp_look[0] = *tmp_pos[0] + tmp[0];
//     *tmp_look[1] = *tmp_pos[1] - tmp[1];
// }

// void calc_intersect_wall(t_hold *hold)
// {
//     float tmp_pos[2];
//     float tmp_look[2];
//     float tmp[2];

//     tmp_pos[0] = hold->pos[0];
//     tmp_pos[1] = hold->pos[1];
//     tmp_look[0] = hold->look[0];
//     tmp_look[1] = hold->look[1];
//     tmp[0] = tmp_look[0] - tmp_pos[0];
//     tmp[1] = tmp_pos[1] - tmp_look[1];
//     int32_t i =0;
//     while (1)
//     {
//         draw_line(hold, tmp_pos[0], tmp_pos[1], tmp_look[0], tmp_look[1], 0x2f4f4f);
//         if (hit_wall(hold, tmp_pos[0], tmp_pos[1]) == true)
//         {
//             printf("hit a wallll\n");
//             exit(0);
//             break;
//         }
//         // next_step(&tmp_pos, &tmp_look);
//         // printf()
//         tmp_pos[0] = tmp_pos[0] + (tmp_look[0] - tmp_pos[0]);
//         tmp_pos[1] = tmp_pos[1] + (tmp_look[1] - tmp_pos[1]);
//         tmp_look[0] = tmp_pos[0] + tmp[0];
//         tmp_look[1] = tmp_pos[1] - tmp[1];
//     tmp[0] = tmp_look[0] - tmp_pos[0];
//     tmp[1] = tmp_pos[1] - tmp_look[1];
//         draw_line(hold, tmp_pos[0], tmp_pos[1], tmp_look[0], tmp_look[1], 0xeedd82);
//         // sleep(2);
//         i++;
//     }
// }

// void raycast(t_hold *hold)
// {
//     int32_t x =0;
//     while (x<WIDHT)
//     {
//         calc_intersect_wall(hold);
//         // calc_distance_wall_to_plane();
//         // draw_vertical_line();
//         x++;
//     }
// }

int main(int argc, char **argv)
{
    t_hold hold;
    (void)argc;
    
    check_4_general_errors(argv, argc);
    init_structs(&hold, argv);
    initialize_mlx(&hold);
    parse(&hold, hold.cub);

    put_image(&hold);


    // mlx_hook(hold.mlx_win, 2, 0, key_hook, &hold);
    // mlx_loop_hook(hold.mlx, update_dot_position, &hold);
    mlx_do_sync(hold.mlx);
    mlx_loop(hold.mlx);
}




//! NEXT:
// - create 2d map
// - key also works if pressed


//! GENERAL:
// - optim Makefile 
//      -> .o files in object folder
//      -> libmlx.dylib autom in root of CUB