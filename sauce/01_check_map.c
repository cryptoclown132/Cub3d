#include "../inc/cub3d.h"

void	map_closed_2(t_cub *cub, int i, int j)
{
	if (cub->map[i][j] == '0')
	{
		if (i == 0 || j == 0 || i + 1 == cub->map_rows
			|| j + 1 == cub->map_columns || !cub->map[i][j + 1]
			|| !cub->map[i][j - 1] || !cub->map[i + 1][j]
			|| !cub->map[i + 1][j + 1] || !cub->map[i + 1][j -1]
			|| !cub->map[i - 1][j] || !cub->map[i - 1][j + 1]
			|| !cub->map[i + 1][j] || cub->map[i][j + 1] == ' '
			|| cub->map[i][j - 1] == ' ' || cub->map[i + 1][j] == ' '
			|| cub->map[i + 1][j + 1] == ' ' || cub->map[i + 1][j -1] == ' '
			|| cub->map[i - 1][j] == ' ' || cub->map[i - 1][j + 1] == ' '
			|| cub->map[i + 1][j] == ' ')
			error_free("Map in not closed!", cub);
	}
}

void	player_in_map(t_cub *cub, int i, int j)
{
	if (cub->map[i][j] == 'S' || cub->map[i][j] == 'N'
		|| cub->map[i][j] == 'W' || cub->map[i][j] == 'E')
	{
		if (i == 0 || j == 0 || i + 1 == cub->map_rows
			|| j + 1 == cub->map_columns || !cub->map[i][j + 1]
			|| !cub->map[i][j - 1] || !cub->map[i + 1][j]
			|| !cub->map[i + 1][j + 1] || !cub->map[i + 1][j -1]
			|| !cub->map[i - 1][j] || !cub->map[i - 1][j + 1]
			|| !cub->map[i + 1][j] || cub->map[i][j + 1] == ' '
			|| cub->map[i][j - 1] == ' ' || cub->map[i + 1][j] == ' '
			|| cub->map[i + 1][j + 1] == ' ' || cub->map[i + 1][j -1] == ' '
			|| cub->map[i - 1][j] == ' ' || cub->map[i - 1][j + 1] == ' '
			|| cub->map[i + 1][j] == ' ')
			error_free("Player outside of the map!", cub);
	}
}

int	empty_rows_2(t_cub *cub, int i)
{
	while (cub->map[++i])
	{
		if (ft_strchr(cub->map[i], 'S') || ft_strchr(cub->map[i], 'N')
			|| ft_strchr(cub->map[i], 'W') || ft_strchr(cub->map[i], 'E')
			|| ft_strchr(cub->map[i], '1') || ft_strchr(cub->map[i], '0'))
			error_free("Map has to be one part!", cub);
	}
	return (i);
}

void	empty_rows(t_cub *cub)
{
	int	i;

	i = -1;
	while (cub->map[++i])
	{
		if (!ft_strchr(cub->map[i], 'S') && !ft_strchr(cub->map[i], 'N')
			&& !ft_strchr(cub->map[i], 'W') && !ft_strchr(cub->map[i], 'E')
			&& !ft_strchr(cub->map[i], '1') && !ft_strchr(cub->map[i], '0'))
			empty_rows_2(cub, i);
	}
}

void	check_player(int player, t_cub *cub)
{
	if (player < 1)
		error_free("No player on the map!", cub);
	else if (player > 1)
		error_free("There is more than one player on the map!", cub);
}
