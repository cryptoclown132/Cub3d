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
		hold->plane[1] = 0.9;
	}
	else if (player == 'W')
	{
		hold->dirx = -1;
		hold->diry = 0;
		hold->plane[0] = 0;
		hold->plane[1] = -0.9;
	}
}

void	valid_elem(t_hold *hold)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	if (!hold->map)
		error_free("No map existing!", hold);
	while (hold->map[i])
	{
		j = 0;
		while (hold->map[i][j])
		{
			if (hold->map[i][j] == 'S' || hold->map[i][j] == 'N'
				|| hold->map[i][j] == 'W' || hold->map[i][j] == 'E')
			{
				update_data(hold, j, i, hold->map[i][j]);
				player++;
			}
			else if (hold->map[i][j] != '1' && hold->map[i][j] != '0'
				&& hold->map[i][j] != ' ' && hold->map[i][j] != '\n')
				error_free("Wrong element in the map!", hold);
			j++;
		}
		i++;
	}
	check_player(player, hold);
}

void	map_closed(t_hold *hold)
{
	int	i;
	int	j;

	i = -1;
	while (hold->map[++i])
	{
		j = -1;
		while (hold->map[i][++j])
		{
			map_closed_2(hold, i, j);
			player_in_map(hold, i, j);
		}
	}
}

void	resize_line(t_hold *hold, int i)
{
	int		j;
	char	*tmp;

	tmp = malloc((hold->map_columns + 1) * sizeof(char));
	if (!tmp)
		error_free("Failed to Malloc!", hold);
	j = -1;
	while (hold->map[i][++j])
	{
		tmp[j] = hold->map[i][j];
	}
	while (j < hold->map_columns)
		tmp[j++] = ' ';
	tmp[j] = '\0';
	free(hold->map[i]);
	hold->map[i] = tmp;
}

void	resize_map(t_hold *hold)
{
	int	i;
	int	j;

	i = -1;
	while (hold->map[++i])
	{
		j = ft_strlen(hold->map[i]);
		if (j < hold->map_columns)
			resize_line(hold, i);
	}
}

void	check_map(t_hold *hold)
{
	valid_elem(hold);
	empty_rows(hold);
	resize_map(hold);
	map_closed(hold);
}
