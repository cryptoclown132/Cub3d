/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkroger <jkroger@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:40:11 by jkroger           #+#    #+#             */
/*   Updated: 2023/04/24 13:43:35 by jkroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_space_tab(int i, char *line)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int	check_file(char *file)
{
	int	i;

	i = -1;
	while (file[++i])
	{
		if (file[i] == '.' && file[i + 1] == 'c' && file[i + 2] == 'u'
			&& file[i + 3] == 'b' && !file[i + 4])
			return (1);
	}
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
