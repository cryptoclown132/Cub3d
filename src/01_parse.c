#include "../inc/cub3d.h"

void	count_rows(t_hold *hold)
{
	char	*line;

	line = get_next_line(hold->fd);
	while (line)
	{
		hold->map_rows++;
		free(line);
		line = get_next_line(hold->fd);
	}
	close(hold->fd);
}

void	init_map_2(t_hold *hold, char *line)
{
	int	j;
	int	i;

	j = 0;
	while (line)
	{
		i = ft_strlen(line);
		if (i > hold->map_columns)
			hold->map_columns = i;
		if (ft_strchr(line, '\n'))
			hold->map[j++] = ft_substr(line, 0, ft_strlen(line) - 1);
		else
			hold->map[j++] = ft_strdup(line);
		free(line);
		line = get_next_line(hold->fd);
	}
	hold->map[j] = NULL;
}

void	init_map(t_hold *hold)
{
	char	*line;
	int		i;

	hold->map_columns = 0;
	count_rows(hold);
	hold->map = malloc((hold->map_rows + 1) * sizeof(char *));
	if (!hold->map)
		error_free("Failed to Malloc!", hold);
	hold->fd = open(hold->file_name, O_RDONLY);
	if (hold->fd < 0)
		error_free(strerror(errno), hold);
	line = get_next_line(hold->fd);
	while (line)
	{
		i = skip_space_tab(0, line);
		if (line[i] == '1' || line[i] == '0')
		{
			init_map_2(hold, line);
			break ;
		}
		free(line);
		line = get_next_line(hold->fd);
	}
	close(hold->fd);
}