#ifndef CUB3D_H
# define CUB3D_H


// ----------------------------------------------------------------------------
//!		INCLUDES:
#include <stdlib.h>
#include <errno.h>		// errno
#include <unistd.h>
#include <stdio.h>		// debugging
#include <math.h>		// cos and sin
# include <stdbool.h>	// bool
# include <fcntl.h>	    // open func
# include <limits.h>	// for macros
# include "../MLX/mlx.h"
# include "../libft/libft.h"


// ----------------------------------------------------------------------------
//!		MACROS:
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

# define WINDOW_NAME "u gay"
# define WIDHT 1000
# define HEIGHT 700
# define ROTATION_ANGLE 0.06

// get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif


#define PLAYER_POSITION_X 500//delete later
#define PLAYER_POSITION_Y 200//delete later

# define MLX_ERROR -1

// # define SPEED 5 // implement later if possible

// maybe hc later in beginning of program:
// # define TILE_SIZE 1
// # define STEPS_PER_TILE 10
// # define LINE_LEN TILE_SIZE/STEPS_PER_TILE
# define LINE_LEN 4
// keycodes:
# define LEFT 123
# define RIGHT 124
# define W 13
# define A 0
# define S 1
# define D 2
# define ESCAPE 53

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
//!		STRUCTS:
// ju's structs
typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	int		height;
	int		width;
}				t_img;

typedef struct s_minimap
{
	float	pos[2];
	float	look[2];
}				t_minimap;

typedef struct s_cub
{
	int		floor_colour;
	int		ceiling_colour;
	char	*ceiling;
	char	*floor;
	t_img	*img;
	t_img	*img_2;
	t_img	*img_north;
	t_img	*img_east;
	t_img	*img_south;
	t_img	*img_west;
	
	double	wallx;
	int		tex_x;
	int		tex_y;
	int		tex_start;
	int		tex_end;
	int		line_height;
	
	int		fd;
	int		map_rows;
	int		map_columns;
	char	player_dir;
	char	**map;
	//check for correct path
	char	*path_north;
	char	*path_east;
	char	*path_south;
	char	*path_west;
	char	*file_name;
}				t_cub;




typedef struct s_hold
{
	void	*mlx;
	void	*mlx_win;
	void	*img_ptr;
	char	*data_addr;
	void	*player_img_ptr;
	char	*player_addr;
	int32_t bits_per_pixel;
	int32_t size_line;
	int32_t endian;

	float	pos[2];
	float	look[2];
	int32_t	map_pos[2];
	int32_t	step[2];

	float	delta_dist[2];
	float	wall_dist;
	float	side_dist[2];
	int32_t	side;

	float	wall[2];
	float angle;
	bool go;
	struct s_cub	*cub;
	struct s_minimap	*minimap;
}						t_hold;

// ----------------------------------------------------------------------------
// !		FUNCTIONS:
// void	raycast(t_hold *hold);
void draw_line(t_hold *hold, int x0, int y0, int x1, int y1, int color);
// void	my_mlx_pixel_put(t_hold *hold, int x, int y, int color);
void init_minimap(t_hold *hold);
int32_t init_hold(t_hold *hold);
int32_t create_window(t_hold *hold);
int32_t	destroy_window(t_hold *hold);


// !	RAYCAST:
void dda(t_hold *hold);


// !	GETNEXTLINE:
void	buff_after_line(char *buff);
char	*create_last(char *buff, char *line);
char	*get_next_line(int fd);


// !	KEYEVENTS:
int32_t update_dot_position(t_hold *hold);
float pi_val(int32_t keycode, char *sin_or_cos);
void calc_new_coordinate(t_hold *hold, int32_t keycode);
void calc_new_look_dir(t_hold *hold, int32_t keycode);
int32_t key_hook(int keycode, t_hold *hold);


// !	ERROR:
void	ft_error(char *err_msg);
void	error_free(char *err_msg, t_cub *cub);


// !	CUBUTILS:
int	skip_space_tab(int i, char *line);
void	check_file(char *file);


// !	CHEKMAP:
//	00_
void	valid_elem(t_hold *hold, t_cub *cub);
void	map_closed(t_cub *cub);
void	resize_line(t_cub *cub, int i);
void	resize_map(t_cub *cub);
void	check_map(t_hold *hold, t_cub *cub);
//	01_
void	map_closed_2(t_cub *cub, int i, int j);
void	player_in_map(t_cub *cub, int i, int j);
int		empty_rows_2(t_cub *cub, int i);
void	empty_rows(t_cub *cub);
void	check_player(int player, t_cub *cub);


// !	PARSE:
// 00_
char	*get_path(char *line, int i);
int	check_line(t_cub *cub, char *line);
void	parse(t_hold *hold, t_cub *cub);
// 01_
void	count_rows(t_cub *cub);
void	init_map_2(t_cub *cub, char *line);
void	init_map(t_cub *cub);



// delete_later.c
void draw_my_map2(t_hold *hold);
void draw_hc_map(t_hold *hold);
void draw_line_of_view_of_player(t_hold *hold);
void init_put_line(t_hold *hold, double want_x, double want_y);
void draw_grit(t_hold *hold);
void draw_looking_direction(t_hold *hold);
void put_cross(t_hold *hold,int x, int y);
void put_info_on_window(t_hold *hold);


//my stuff
void	put_image(t_hold *hold);
void	init_images(t_hold *hold);
int		get_colour(t_cub *cub, char *rgb);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	colours_and_images(t_hold *hold);

void raycast(t_hold *hold, int x);
#endif