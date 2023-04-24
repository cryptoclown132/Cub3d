/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:25:38 by jkroger           #+#    #+#             */
/*   Updated: 2023/04/24 13:40:07 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_cub *cub, char *file)
{
	cub->map_rows = 1;
	cub->map_columns = 0;
	cub->player_dir = '\0';
	cub->map = NULL;
	cub->ceiling = NULL;
	cub->floor = NULL;
	cub->path_east = NULL;
	cub->path_west = NULL;
	cub->path_north = NULL;
	cub->path_south = NULL;
	cub->file_name = ft_strdup(file);
	cub->mlx = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx, WIDHT, HEIGHT, "whatever");
}

int	main(int argc, char *argv[])
{
	t_cub	*cub;

	if (argc != 2)
		ft_error("Number of arguments must be 2!");
	if (!check_file(argv[1]))
		ft_error("Wrong file extension! It has to be: .cub");
	cub = malloc(sizeof(t_cub));
	if (!cub)
		ft_error("Failed to Malloc!");
	init(cub, argv[1]);
	parse(cub);
	put_image(cub);
	mlx_loop(cub->mlx);
}
