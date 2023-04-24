/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:53:22 by jkroger           #+#    #+#             */
/*   Updated: 2023/04/24 13:44:35 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUBD3D_H
#  define CUBD3D_H
# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>	// bool
# include <fcntl.h>	    // open func
# include <limits.h>	// for macros
# include "../libft/libft.h"
# include <string.h>
# include <sys/errno.h>
# include <math.h>


// ----------------------------------------------------------------------------
//!		Macros:
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

# define WINDOW_NAME "Das ist ein window lol"
# define WIDHT 1000
# define HEIGHT 700
# define MLX_ERROR -1
# define ESCAPE 53
# define TEXWIDTH 64 //check
# define TEXHEIGHT 64 //check
// ----------------------------------------------------------------------------
//!		Structs:

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	int		height;
	int		width;
}				t_img;

typedef struct s_cub
{
	int		floor_colour;
	int		ceiling_colour;
	t_img	*img;
	t_img	*img_2;
	t_img	*img_north;
	t_img	*img_south;
	t_img	*img_west;
	t_img	*img_east;
	
	double	player_pos_x;
	double	player_pos_y;
	int		map_pos_x;
	int		map_pos_y;
	double	wallx;
	int		tex_x;
	int		tex_y;
	int		tex_start;
	int		tex_end;
	int		line_height;

	
	double	raydir_x;
	double	raydir_y;
	int		side;
	double	perpWallDist;

	
	
	int		fd;
	int		map_rows;
	int		map_columns;
	char	player_dir;
	char	**map;
	char	*ceiling;
	char	*floor;
	//check for correct path
	char	*path_east;
	char	*path_west;
	char	*path_north;
	char	*path_south;
	char	*file_name;
	void	*mlx;
	void	*mlx_win;
}						t_cub;

// error.c
void	ft_error(char *err_msg);
void	error_free(char *err_msg, t_cub *cub);

// parse.c
void	parse(t_cub *cub);

// parse_map.c
void	init_map(t_cub *cub);

// cub_utils.c
int	skip_space_tab(int i, char *line);
int	check_file(char *file);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

// check_map.c
void	check_map(t_cub *cub);

// check_map_2.c
void	map_closed_2(t_cub *cub, int i, int j);
void	player_in_map(t_cub *cub, int i, int j);
void	empty_rows(t_cub *cub);
void	check_player(int player, t_cub *cub);

// close.c
void	close_and_free(t_cub *cub);


/* textures */
void	put_image(t_cub *cub);
int		get_colour(t_cub *cub, char *rgb);
void	init_images(t_cub *cub);

//ray_casting.c
void	ray_casting(t_cub *cub);

# endif