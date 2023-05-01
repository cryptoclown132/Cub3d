/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:49:39 by jkroger           #+#    #+#             */
/*   Updated: 2023/05/01 17:23:59 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/cub3d.h"
# include "../libft/libft.h"

void	put_texture(t_img *img, t_hold *hold, int x, int y)
{
	int	color;

	color = *(int *)(img->addr + ((int)(hold->tex_y) % \
		img->height * img->line_length + hold->tex_x % img->width * \
		(img->bits_per_pixel / 8)));
	my_mlx_pixel_put(hold->img, x, y, color);
}

void	texture_coordinates(t_img *img, t_hold *hold)
{
	if (hold->side == 0)
		hold->wallx = hold->pos[1] + hold->wall_dist * hold->look[1];
	else
		hold->wallx = hold->pos[0] + hold->wall_dist * hold->look[0];
	hold->wallx -= floor((hold->wallx));
	hold->tex_x = (int)(hold->wallx * (double)img->width);
	if (hold->side == 0 && hold->look[0] > 0)
		hold->tex_x = img->width - hold->tex_x - 1;
	if (hold->side == 1 && hold->look[1] < 0)
		hold->tex_x = img->width - hold->tex_x - 1;
}

void	put_image_height(t_img *img, t_hold *hold, int x)
{
	int		y;
	double	step;
	double	tex_pos;

	y = -1;
	step = 1.0 * img->height / hold->line_height;
	tex_pos = (hold->tex_start - HEIGHT / 2 + hold->line_height / 2) * step;
	texture_coordinates(img, hold);
	while (++y < HEIGHT && y <= hold->tex_start)
		my_mlx_pixel_put(hold->img, x, y, hold->floor_colour);
	while (y < HEIGHT && y <= hold->tex_end)
	{
		hold->tex_y = (int)tex_pos & (img->height - 1);
		tex_pos += step;
		put_texture(img, hold, x, y);
		y++;
	}
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(hold->img, x, y, hold->ceiling_colour);
		y++;
	}
}

t_img	*which_texture(t_hold *hold)
{
	if (((hold->look[0] <= 0 && hold->look[1] <= 0)
			|| (hold->look[0] >= 0 && hold->look[1] <= 0))
		&& hold->side == 1)
		return (hold->img_north);
	else if (((hold->look[0] >= 0 && hold->look[1] >= 0)
			|| (hold->look[0] <= 0 && hold->look[1] >= 0))
		&& hold->side == 1)
		return (hold->img_south);
	else if (((hold->look[0] <= 0 && hold->look[1] <= 0)
			|| (hold->look[0] <= 0 && hold->look[1] >= 0))
		&& hold->side == 0)
		return (hold->img_west);
	else if (((hold->look[0] >= 0 && hold->look[1] >= 0)
			|| (hold->look[0] >= 0 && hold->look[1] <= 0))
		&& hold->side == 0)
		return (hold->img_east);
	else
		error_free("No direction to indicate the texture!", hold);
	return (NULL);
}

void	put_image(t_hold *hold)
{
	int	x;
	x = -1;
	while (++x < WIDHT)
	{
		raycast(hold, x);
		put_image_height(which_texture(hold), hold, x);
	}
	mlx_put_image_to_window(hold->mlx, hold->mlx_win, hold->img->img, 0, 0);
}


void	colours_and_images(t_hold *hold)
{
	hold->floor_colour = get_colour(hold, hold->floor);
	hold->ceiling_colour = get_colour(hold, hold->ceiling);
	init_images(hold);
}
