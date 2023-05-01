/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:47:35 by jkroger           #+#    #+#             */
/*   Updated: 2023/05/01 19:47:43 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*get_path(char *line, int i)
{
	char	*path;
	int		j;

	i = skip_space_tab(++i, line);
	j = i;
	while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '\n')
		j++;
	path = ft_substr(line, i, j - i);
	return (path);
}

int	check_line(t_hold *hold, char *line)
{
	int	i;

	i = skip_space_tab(0, line);
	if (line[i] == 'N' && line[i + 1] == 'O')
		hold->path_north = get_path(line, ++i);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		hold->path_south = get_path(line, ++i);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		hold->path_west = get_path(line, ++i);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		hold->path_east = get_path(line, ++i);
	else if (line[i] == 'F')
		hold->floor = get_path(line, i);
	else if (line[i] == 'C')
		hold->ceiling = get_path(line, i);
	else if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

void	parse(t_hold *hold)
{
	char	*line;

	hold->fd = open(hold->file_name, O_RDONLY);
	if (hold->fd < 0)
		error_free(strerror(errno), hold);
	line = get_next_line(hold->fd);
	while (line)
	{
		if (check_line(hold, line))
		{
			free(line);
			init_map(hold);
			break ;
		}
		free(line);
		line = get_next_line(hold->fd);
	}
	if (!hold->map)
	{
		printf("map access kagge\n");
		close(hold->fd);
	}
	check_map(hold);
}
