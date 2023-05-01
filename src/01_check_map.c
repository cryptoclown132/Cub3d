#include "../inc/cub3d.h"

void	map_closed_2(t_hold *hold, int i, int j)
{
	if (hold->map[i][j] == '0')
	{
		if (i == 0 || j == 0 || i + 1 == hold->map_rows
			|| j + 1 == hold->map_columns || !hold->map[i][j + 1]
			|| !hold->map[i][j - 1] || !hold->map[i + 1][j]
			|| !hold->map[i + 1][j + 1] || !hold->map[i + 1][j -1]
			|| !hold->map[i - 1][j] || !hold->map[i - 1][j + 1]
			|| !hold->map[i + 1][j] || hold->map[i][j + 1] == ' '
			|| hold->map[i][j - 1] == ' ' || hold->map[i + 1][j] == ' '
			|| hold->map[i + 1][j + 1] == ' ' || hold->map[i + 1][j -1] == ' '
			|| hold->map[i - 1][j] == ' ' || hold->map[i - 1][j + 1] == ' '
			|| hold->map[i + 1][j] == ' ')
			error_free("Map in not closed!", hold);
	}
}

void	player_in_map(t_hold *hold, int i, int j)
{
	if (hold->map[i][j] == 'S' || hold->map[i][j] == 'N'
		|| hold->map[i][j] == 'W' || hold->map[i][j] == 'E')
	{
		if (i == 0 || j == 0 || i + 1 == hold->map_rows
			|| j + 1 == hold->map_columns || !hold->map[i][j + 1]
			|| !hold->map[i][j - 1] || !hold->map[i + 1][j]
			|| !hold->map[i + 1][j + 1] || !hold->map[i + 1][j -1]
			|| !hold->map[i - 1][j] || !hold->map[i - 1][j + 1]
			|| !hold->map[i + 1][j] || hold->map[i][j + 1] == ' '
			|| hold->map[i][j - 1] == ' ' || hold->map[i + 1][j] == ' '
			|| hold->map[i + 1][j + 1] == ' ' || hold->map[i + 1][j -1] == ' '
			|| hold->map[i - 1][j] == ' ' || hold->map[i - 1][j + 1] == ' '
			|| hold->map[i + 1][j] == ' ')
			error_free("Player outside of the map!", hold);
	}
}

int	empty_rows_2(t_hold *hold, int i)
{
	while (hold->map[++i])
	{
		if (ft_strchr(hold->map[i], 'S') || ft_strchr(hold->map[i], 'N')
			|| ft_strchr(hold->map[i], 'W') || ft_strchr(hold->map[i], 'E')
			|| ft_strchr(hold->map[i], '1') || ft_strchr(hold->map[i], '0'))
			error_free("Map has to be one part!", hold);
	}
	return (i);
}

void	empty_rows(t_hold *hold)
{
	int	i;

	i = -1;
	while (hold->map[++i])
	{
		if (!ft_strchr(hold->map[i], 'S') && !ft_strchr(hold->map[i], 'N')
			&& !ft_strchr(hold->map[i], 'W') && !ft_strchr(hold->map[i], 'E')
			&& !ft_strchr(hold->map[i], '1') && !ft_strchr(hold->map[i], '0'))
			empty_rows_2(hold, i);
	}
}

void	check_player(int player, t_hold *hold)
{
	if (player < 1)
		error_free("No player on the map!", hold);
	else if (player > 1)
		error_free("There is more than one player on the map!", hold);
}
