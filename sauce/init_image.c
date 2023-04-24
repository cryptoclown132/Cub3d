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
	hold->cub->img_east = malloc(sizeof(t_img));
	if (!hold->cub->img_east)
		error_free("Failed to malloc!", hold->cub);
	hold->cub->img_east->width = 0;
	hold->cub->img_east->height = 0;
	hold->cub->img_east->img = mlx_xpm_file_to_image(hold->mlx, hold->cub->path_east,
			&hold->cub->img_east->width, &hold->cub->img_east->height);
	if (!hold->cub->img_east->img)
		error_free("Path to image wrong!", hold->cub);
	hold->cub->img_east->addr = mlx_get_data_addr(hold->cub->img_east->img,
			&hold->cub->img_east->bits_per_pixel,
			&hold->cub->img_east->line_length, &hold->cub->img_east->endian);
}

void	init_images_2(t_hold *hold)
{
	hold->cub->img_south = malloc(sizeof(t_img));
	if (!hold->cub->img_south)
		error_free("Failed to malloc!", hold->cub);
	hold->cub->img_south->width = 0;
	hold->cub->img_south->height = 0;
	hold->cub->img_south->img = mlx_xpm_file_to_image(hold->mlx, hold->cub->path_south,
			&hold->cub->img_south->width, &hold->cub->img_south->height);
	if (!hold->cub->img_south->img)
		error_free("Path to image wrong!", hold->cub);
	hold->cub->img_south->addr = mlx_get_data_addr(hold->cub->img_south->img,
			&hold->cub->img_south->bits_per_pixel, &hold->cub->img_south->line_length,
			&hold->cub->img_south->endian);
	hold->cub->img_west = malloc(sizeof(t_img));
	if (!hold->cub->img_west)
		error_free("Failed to malloc!", hold->cub);
	hold->cub->img_west->width = 0;
	hold->cub->img_west->height = 0;
	hold->cub->img_west->img = mlx_xpm_file_to_image(hold->mlx, hold->cub->path_west,
			&hold->cub->img_west->width, &hold->cub->img_west->height);
	if (!hold->cub->img_west->img)
		error_free("Path to image wrong!", hold->cub);
	hold->cub->img_west->addr = mlx_get_data_addr(hold->cub->img_west->img,
			&hold->cub->img_west->bits_per_pixel,
			&hold->cub->img_west->line_length, &hold->cub->img_west->endian);
	init_images_3(hold);
}

void	init_images(t_hold *hold)
{
	hold->cub->img = malloc(sizeof(t_img));
	if (!hold->cub->img)
		error_free("Failed to malloc!", hold->cub);
	hold->cub->img->img = mlx_new_image(hold->mlx, WIDHT, HEIGHT);
	hold->cub->img->addr = mlx_get_data_addr(hold->cub->img->img,
			&hold->cub->img->bits_per_pixel,
			&hold->cub->img->line_length, &hold->cub->img->endian);
	hold->cub->img_north = malloc(sizeof(t_img));
	if (!hold->cub->img_north)
		error_free("Failed to malloc!", hold->cub);
	hold->cub->img_north->width = 0;
	hold->cub->img_north->height = 0;
	hold->cub->img_north->img = mlx_xpm_file_to_image(hold->mlx, hold->cub->path_north,
			&hold->cub->img_north->width, &hold->cub->img_north->height);
	if (!hold->cub->img_north->img)
		error_free("Path to image wrong!", hold->cub);
	hold->cub->img_north->addr = mlx_get_data_addr(hold->cub->img_north->img,
			&hold->cub->img_north->bits_per_pixel,
			&hold->cub->img_north->line_length, &hold->cub->img_north->endian);
	init_images_2(hold);
}
