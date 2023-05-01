/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hold3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:11:27 by jkroger           #+#    #+#             */
/*   Updated: 2023/05/01 17:18:00 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define ROTATION_ANGLE 0.2
# define SPEED 0.25

// get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif


# define MLX_ERROR -1

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

typedef struct s_hold
{
	t_img	*img;
	t_img	*img_north;
	t_img	*img_east;
	t_img	*img_south;
	t_img	*img_west;
	void	*mlx;
	void	*mlx_win;
	char	**map;
	char	*ceiling;
	char	*floor;
	char	*path_north;
	char	*path_east;
	char	*path_south;
	char	*path_west;
	char	*file_name;
	char	player_dir;
	double	pos[2];
	double	look[2];
	double	plane[2];
	double	delta_dist[2];
	double	side_dist[2];
	double	wall_dist;
	double	dirx;
	double	diry;
	double	wallx;
	int32_t	map_pos[2];
	int32_t	step[2];
	int32_t	side;
	int32_t		floor_colour;
	int32_t		ceiling_colour;
	int32_t		tex_x;
	int32_t		tex_y;
	int32_t		tex_start;
	int32_t		tex_end;
	int32_t		line_height;
	int32_t		fd;
	int32_t		map_rows;
	int32_t		map_columns;
}						t_hold;

// ----------------------------------------------------------------------------
// !		FUNCTIONS:


// !	RAYCAST:
void dda(t_hold *hold);


// !	GETNEXTLINE:
void	buff_after_line(char *buff);
char	*create_last(char *buff, char *line);
char	*get_next_line(int fd);


// !	KEYEVENTS:
int32_t key_hook(int keycode, t_hold *hold);


// !	ERROR:
void	ft_error(char *err_msg);
void	error_free(char *err_msg, t_hold *hold);


// !	holdUTILS:
int	skip_space_tab(int i, char *line);
void	check_file(char *file);


// !	CHEKMAP:
//	00_
void	valid_elem(t_hold *hold);
void	map_closed(t_hold *hold);
void	resize_line(t_hold *hold, int i);
void	resize_map(t_hold *hold);
void	check_map(t_hold *hold);
//	01_
void	map_closed_2(t_hold *hold, int i, int j);
void	player_in_map(t_hold *hold, int i, int j);
int		empty_rows_2(t_hold *hold, int i);
void	empty_rows(t_hold *hold);
void	check_player(int player, t_hold *hold);


// !	PARSE:
// 00_
char	*get_path(char *line, int i);
int	check_line(t_hold *hold, char *line);
void	parse(t_hold *hold);
// 01_
void	count_rows(t_hold *hold);
void	init_map_2(t_hold *hold, char *line);
void	init_map(t_hold *hold);


//my stuff
void	put_image(t_hold *hold);
void	init_images(t_hold *hold);
int		get_colour(t_hold *hold, char *rgb);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	colours_and_images(t_hold *hold);

int	close_and_free(t_hold *hold);

void raycast(t_hold *hold, int x);
#endif