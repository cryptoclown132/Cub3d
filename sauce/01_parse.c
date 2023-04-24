#include "../inc/cub3d.h"

void	count_rows(t_cub *cub)
{
	char	*line;

	line = get_next_line(cub->fd);
	while (line)
	{
		cub->map_rows++;
		free(line);
		line = get_next_line(cub->fd);
	}
	close(cub->fd);
}

void	init_map_2(t_cub *cub, char *line)
{
	int	j;
	int	i;

	j = 0;
	while (line)
	{
		i = ft_strlen(line);
		if (i > cub->map_columns)
			cub->map_columns = i;
		if (ft_strchr(line, '\n'))
			cub->map[j++] = ft_substr(line, 0, ft_strlen(line) - 1);
		else
			cub->map[j++] = ft_strdup(line);
		free(line);
		line = get_next_line(cub->fd);
	}
	cub->map[j] = NULL;
}

void	init_map(t_cub *cub)
{
	char	*line;
	int		i;

	cub->map_columns = 0;
	count_rows(cub);
	cub->map = malloc((cub->map_rows + 1) * sizeof(char *));
	if (!cub->map)
		error_free("Failed to Malloc!", cub);
	cub->fd = open(cub->file_name, O_RDONLY);
	if (cub->fd < 0)
		error_free(strerror(errno), cub);
	line = get_next_line(cub->fd);
	while (line)
	{
		i = skip_space_tab(0, line);
		if (line[i] == '1' || line[i] == '0')
		{
			init_map_2(cub, line);
			break ;
		}
		free(line);
		line = get_next_line(cub->fd);
	}
	close(cub->fd);
}