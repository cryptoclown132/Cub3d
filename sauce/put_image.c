/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:49:39 by jkroger           #+#    #+#             */
/*   Updated: 2023/04/24 18:16:36 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/cub3d.h"
# include "../libft/libft.h"

void	put_texture(t_img *img, t_cub *cub, int x, int y)
{
	int	color;

	color = *(int *)(img->addr + ((int)(cub->tex_y) % \
		img->height * img->line_length + cub->tex_x % img->width * \
		(img->bits_per_pixel / 8)));
	my_mlx_pixel_put(cub->img, x, y, color);
}

void	texture_coordinates(t_img *img, t_hold *hold)
{
	if (hold->side == 0)
		hold->cub->wallx = hold->pos[1] + hold->wall_dist * hold->look[1];
	else
		hold->cub->wallx = hold->pos[0] + hold->wall_dist * hold->look[0];
	hold->cub->wallx -= floor((hold->cub->wallx));
	hold->cub->tex_x = (int)(hold->cub->wallx * (double)img->width);
	if (hold->side == 0 && hold->look[0] > 0)
		hold->cub->tex_x = img->width - hold->cub->tex_x - 1;
	if (hold->side == 1 && hold->look[1] < 0)
		hold->cub->tex_x = img->width - hold->cub->tex_x - 1;
}

void	put_image_height(t_img *img, t_hold *hold, int x)
{
	int		y;
	double	step;
	double	tex_pos;

	y = -1;
	step = 1.0 * img->height / hold->cub->line_height;
	tex_pos = (hold->cub->tex_start - HEIGHT / 2 + hold->cub->line_height / 2) * step;
	texture_coordinates(img, hold);
	while (++y < HEIGHT && y <= hold->cub->tex_start)
		my_mlx_pixel_put(hold->cub->img, x, y, hold->cub->floor_colour);
	while (y < HEIGHT && y <= hold->cub->tex_end)
	{
		hold->cub->tex_y = (int)tex_pos & (img->height - 1);
		tex_pos += step;
		put_texture(img, hold->cub, x, y);
		y++;
	}
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(hold->cub->img, x, y, hold->cub->ceiling_colour);
		y++;
	}
}

t_img	*which_texture(t_hold *hold)
{
	if (((hold->look[0] <= 0 && hold->look[1] <= 0)
			|| (hold->look[0] >= 0 && hold->look[1] <= 0))
		&& hold->side == 1)
		return (hold->cub->img_south);
	else if (((hold->look[0] >= 0 && hold->look[1] >= 0)
			|| (hold->look[0] <= 0 && hold->look[1] >= 0))
		&& hold->side == 1)
		return (hold->cub->img_north);
	else if (((hold->look[0] <= 0 && hold->look[1] <= 0)
			|| (hold->look[0] <= 0 && hold->look[1] >= 0))
		&& hold->side == 0)
		return (hold->cub->img_west);
	else if (((hold->look[0] >= 0 && hold->look[1] >= 0)
			|| (hold->look[0] >= 0 && hold->look[1] <= 0))
		&& hold->side == 0)
		return (hold->cub->img_east);
	else
		error_free("No direction to indicate the texture!", hold->cub);
	return (NULL);
}

void	put_image(t_hold *hold)
{
	int	x;
	hold->cub->floor_colour = get_colour(hold->cub, hold->cub->floor);
	hold->cub->ceiling_colour = get_colour(hold->cub, hold->cub->ceiling);
	init_images(hold);
	x = -1;
	while (++x < WIDHT)
	{
		raycast(hold, x);
		// printf("tex_start = %i\n", hold->cub->tex_start);
		put_image_height(which_texture(hold), hold, x);
	}
	mlx_put_image_to_window(hold->mlx, hold->mlx_win, hold->cub->img->img, 0, 0);
}

//side if to know if x or y side was hit
//side 1 is y side
//side 0 x side