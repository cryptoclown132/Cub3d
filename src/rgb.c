/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 13:36:49 by jkroger           #+#    #+#             */
/*   Updated: 2023/04/15 13:36:49 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	convert_colour(int t, int r, int g, int b)
{
	return ((t & 0xff) << 24 | (r & 0xff) << 16 | (g & 0xff) << 8 | (b & 0xff));
}

void	free_rgb(char **rgb_colours)
{
	int	i;

	i = -1;
	if (rgb_colours)
	{
		while (rgb_colours[++i])
			free(rgb_colours[i]);
		free(rgb_colours);
	}
}

int	get_colour(t_hold *hold, char *rgb)
{
	int		i;
	int		colours[3];
	char	**rgb_colours;

	rgb_colours = ft_split(rgb, ',');
	if (!rgb_colours)
		error_free("The number is not a colour!", hold);
	i = -1;
	while (++i < 3 && rgb_colours[i])
		colours[i] = ft_atoi(rgb_colours[i]);
	i = -1;
	while (++i < 3)
	{
		if (!rgb_colours[i] || colours[i] < 0 || colours[i] > 255)
		{
			free_rgb(rgb_colours);
			error_free("The number is not a colour!", hold);
		}
	}
	free_rgb(rgb_colours);
	return (convert_colour(0, colours[0], colours[1], colours[2]));
}
