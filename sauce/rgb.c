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

# include "../inc/cub3d.h"
# include "../libft/libft.h"

int	convert_colour(int t, int r, int g, int b)
{
	return ((t & 0xff) << 24 | (r & 0xff) << 16 | (g & 0xff) << 8 | (b & 0xff));
}

//check that colour is right formated
int	get_colour(t_cub *cub, char *rgb)
{
	int		i;
	int		colours[3];
	char	**rgb_colours;

	rgb_colours = ft_split(rgb, ',');//free
	i = -1;
	while (++i < 3)
		colours[i] = ft_atoi(rgb_colours[i]);
	i = -1;
	while (++i < 3)
	{
		if (colours[i] < 0 || colours[i] > 255)
			error_free("The number is not a colour!", cub);
	}
	i = -1;
	while (++i < 3)
		free(rgb_colours[i]);
	free(rgb_colours);
	return (convert_colour(0, colours[0], colours[1], colours[2]));
}
