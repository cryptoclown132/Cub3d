/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:16:23 by jkroger           #+#    #+#             */
/*   Updated: 2023/04/18 16:03:24 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_path(char *line, int i)
{
	char	*path;
	int		j;

	i = skip_space_tab(++i, line);//can make problems for C and F
	j = i;
	while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '\n')//make change
		j++;
	path = ft_substr(line, i, j - i);//make change
	return (path);
}

int	check_line(t_cub *cub, char *line)
{
	int	i;

	i = skip_space_tab(0, line);
	if (line[i] == 'N' && line[i + 1] == 'O')
		cub->path_north = get_path(line, ++i);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		cub->path_south = get_path(line, ++i);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		cub->path_west = get_path(line, ++i);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		cub->path_east = get_path(line, ++i);
	else if (line[i] == 'F')
		cub->floor = get_path(line, i);
	else if (line[i] == 'C')
		cub->ceiling = get_path(line, i);
	else if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

void	parse(t_cub *cub)
{
	char	*line;

	cub->fd = open(cub->file_name, O_RDONLY);
	if (cub->fd < 0)
		error_free(strerror(errno), cub);
	line = get_next_line(cub->fd);
	while (line)
	{
		if (check_line(cub, line))
		{
			free(line);
			init_map(cub);
			break ;
		}
		free(line);
		line = get_next_line(cub->fd);
	}
	if (!cub->map)
		close(cub->fd);
	check_map(cub);
}
