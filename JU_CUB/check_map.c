/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:55:50 by jkroger           #+#    #+#             */
/*   Updated: 2023/04/16 14:31:17 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	valid_elem(t_cub *cub)
{
	int	i;
	int	j;
	int	player;

	i = -1;
	player = 0;
	if (!cub->map)
		error_free("No map existing!", cub);
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == 'S' || cub->map[i][j] == 'N'
				|| cub->map[i][j] == 'W' || cub->map[i][j] == 'E')
			{
				cub->player_pos_x = i;
				cub->player_pos_y = j;
				cub->player_dir = cub->map[i][j];
				player++;
			}
			else if (cub->map[i][j] != '1' && cub->map[i][j] != '0'
				&& cub->map[i][j] != ' ')
				error_free("Wrong element in the map!", cub);//could give pos.
		}
	}
	check_player(player, cub);
}

void	map_closed(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			map_closed_2(cub, i, j);
			player_in_map(cub, i, j);
		}
	}
}

void	resize_line(t_cub *cub, int i)
{
	int		j;
	char	*tmp;

	tmp = malloc((cub->map_columns + 1) * sizeof(char));
	if (!tmp)
		error_free("Failed to Malloc!", cub);
	j = -1;
	while (cub->map[i][++j])
	{
		tmp[j] = cub->map[i][j];
	}
	while (j < cub->map_columns)
		tmp[j++] = ' ';
	tmp[j] = '\0';
	free(cub->map[i]);
	cub->map[i] = tmp;
}

void	resize_map(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = ft_strlen(cub->map[i]);
		if (j < cub->map_columns)
			resize_line(cub, i);
	}
}

void	check_map(t_cub *cub)
{
	valid_elem(cub);
	empty_rows(cub);
	resize_map(cub);
	map_closed(cub);
}
