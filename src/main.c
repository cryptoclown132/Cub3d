# include "../inc/cub3d.h"
# include "../libft/libft.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


void init_hold(t_hold *hold, char **argv)
{
    // hold = malloc(sizeof(t_hold));
	// if (!hold)
	// 	ft_error("Could not initialize struct!");
	hold->img = NULL;
	hold->img_north = NULL;
	hold->img_east = NULL;
	hold->img_south = NULL;
	hold->img_west = NULL;
	hold->mlx = NULL;
	hold->mlx_win = NULL;
	hold->map = NULL;
	hold->ceiling = NULL;
	hold->floor = NULL;
	hold->path_north = NULL;
	hold->path_east = NULL;
	hold->path_south = NULL;
	hold->path_west = NULL;
	hold->file_name = ft_strdup(argv[1]);
    hold->player_dir = '\0';
    hold->map_rows = 1;
    hold->map_columns = 0;
}

void check_4_general_errors(char **argv, int32_t argc)
{
    if (argc != 2)
		ft_error("Number of arguments must be 2!");
    check_file(argv[1]);
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
}

int32_t game_loop(t_hold *hold)
{
	put_image(hold);
	return(0);
}

void loop(t_hold *hold)
{
	mlx_hook(hold->mlx_win, 17, 0, close_and_free, hold);
	mlx_hook(hold->mlx_win, 2, 0, key_hook, hold);
	mlx_do_sync(hold->mlx);
	mlx_loop(hold->mlx);
}

int main(int argc, char **argv)
{
	t_hold	hold;
	(void)argc;

	check_4_general_errors(argv, argc);
	init_hold(&hold, argv);
	initialize_mlx(&hold);
	parse(&hold);
	colours_and_images(&hold);
    put_image(&hold);
	loop(&hold);
}
