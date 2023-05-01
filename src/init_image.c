/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:49:39 by jkroger           #+#    #+#             */
/*   Updated: 2023/04/15 11:49:39 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_images_3(t_hold *hold)
{
	hold->img_east = malloc(sizeof(t_img));
	if (!hold->img_east)
		error_free("Failed to malloc!", hold);
	hold->img_east->width = 0;
	hold->img_east->height = 0;
	hold->img_east->img = mlx_xpm_file_to_image(hold->mlx, hold->path_east,
			&hold->img_east->width, &hold->img_east->height);
	if (!hold->img_east->img)
		error_free("Path to image wrong!", hold);
	hold->img_east->addr = mlx_get_data_addr(hold->img_east->img,
			&hold->img_east->bits_per_pixel,
			&hold->img_east->line_length, &hold->img_east->endian);
}

void	init_images_2(t_hold *hold)
{
	hold->img_south = malloc(sizeof(t_img));
	if (!hold->img_south)
		error_free("Failed to malloc!", hold);
	hold->img_south->width = 0;
	hold->img_south->height = 0;
	hold->img_south->img = mlx_xpm_file_to_image(hold->mlx, hold->path_south,
			&hold->img_south->width, &hold->img_south->height);
	if (!hold->img_south->img)
		error_free("Path to image wrong!", hold);
	hold->img_south->addr = mlx_get_data_addr(hold->img_south->img,
			&hold->img_south->bits_per_pixel, &hold->img_south->line_length,
			&hold->img_south->endian);
	hold->img_west = malloc(sizeof(t_img));
	if (!hold->img_west)
		error_free("Failed to malloc!", hold);
	hold->img_west->width = 0;
	hold->img_west->height = 0;
	hold->img_west->img = mlx_xpm_file_to_image(hold->mlx, hold->path_west,
			&hold->img_west->width, &hold->img_west->height);
	if (!hold->img_west->img)
		error_free("Path to image wrong!", hold);
	hold->img_west->addr = mlx_get_data_addr(hold->img_west->img,
			&hold->img_west->bits_per_pixel,
			&hold->img_west->line_length, &hold->img_west->endian);
	init_images_3(hold);
}

void	init_images(t_hold *hold)
{
	hold->img = malloc(sizeof(t_img));
	if (!hold->img)
		error_free("Failed to malloc!", hold);
	hold->img->img = mlx_new_image(hold->mlx, WIDHT, HEIGHT);
	hold->img->addr = mlx_get_data_addr(hold->img->img,
			&hold->img->bits_per_pixel,
			&hold->img->line_length, &hold->img->endian);
	hold->img_north = malloc(sizeof(t_img));
	if (!hold->img_north)
		error_free("Failed to malloc!", hold);
	hold->img_north->width = 0;
	hold->img_north->height = 0;
	hold->img_north->img = mlx_xpm_file_to_image(hold->mlx, hold->path_north,
			&hold->img_north->width, &hold->img_north->height);
	if (!hold->img_north->img)
		error_free("Path to image wrong!", hold);
	hold->img_north->addr = mlx_get_data_addr(hold->img_north->img,
			&hold->img_north->bits_per_pixel,
			&hold->img_north->line_length, &hold->img_north->endian);
	init_images_2(hold);
}
