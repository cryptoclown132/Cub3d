#include "../inc/cub3d.h"

void update_data(t_hold *hold, int j, int i, char player)
{
	hold->map_pos[0] = j;
	hold->map_pos[1] = i;
	hold->pos[0] = j +0.5;
	hold->look[0] = i +0.5;
	hold->pos[1] = i +0.5;
	hold->look[1] = j +0.5-LINE_LEN;

	if (player == 'S')
	{
		hold->dirx = 0;
		hold->diry = 1;
		hold->plane[0] = -0.9;
		hold->plane[1] = 0;
	}
	else if (player == 'N')
	{
		hold->dirx = 0;
		hold->diry = -1;
		hold->plane[0] = 0.9;
		hold->plane[1] = 0;
	}
	else if (player == 'E')
	{
		hold->dirx = 1;
		hold->diry = 0;
		hold->plane[0] = 0;
		hold->plane[1] = -0.9;
	}
	else if (player == 'W')
	{
		hold->dirx = -1;
		hold->diry = 0;
		hold->plane[0] = 0;
		hold->plane[1] = 0.9;
	}
}

void	valid_elem(t_hold *hold, t_cub *cub)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	if (!cub->map)
		error_free("No map existing!", cub);
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'S' || cub->map[i][j] == 'N'
				|| cub->map[i][j] == 'W' || cub->map[i][j] == 'E')
			{//changed i and j here
				update_data(hold, j, i, cub->map[i][j]);
				// hold->map_pos[0] = j;
				// hold->map_pos[1] = i;
				// hold->pos[0] = j +0.5;
				// hold->look[0] = i +0.5;
				// hold->pos[1] = i +0.5;
				// hold->look[1] = j +0.5-LINE_LEN;
				// cub->player_dir = cub->map[i][j];
				// printf("check playerL [%c] pos:[%d][%d]\n", cub->map[i][j], i, j);
				player++;
			}
			else if (cub->map[i][j] != '1' && cub->map[i][j] != '0'
				&& cub->map[i][j] != ' ' && cub->map[i][j] != '\n')
				error_free("Wrong element in the map!", cub);//could give pos.
			j++;
		}
		i++;
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

void	check_map(t_hold *hold, t_cub *cub)
{
	valid_elem(hold, cub);
	empty_rows(cub);
	resize_map(cub);
	map_closed(cub);
}
