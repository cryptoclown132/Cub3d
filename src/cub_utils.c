#include "../inc/cub3d.h"

int	skip_space_tab(int i, char *line)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

void	check_file(char *file)
{
	int	i;

	i = -1;
	while (file[++i])
	{
		if (file[i] == '.' && file[i + 1] == 'c' && file[i + 2] == 'u'
			&& file[i + 3] == 'b' && !file[i + 4])
			return ;
	}
	ft_error("Wrong file extension! It has to be: .cub");
}

int	close_and_free(t_hold *hold)
{
	int	i;

	if (hold->ceiling)
		free(hold->ceiling);
	if (hold->floor)
		free(hold->floor);
	if (hold->map)
	{
		i = -1;
		while (hold->map[++i])
			free(hold->map[i]);
		free(hold->map);
	}
	if (hold->path_east)
		free(hold->path_east);
	if (hold->path_north)
		free(hold->path_north);
	if (hold->path_south)
		free(hold->path_south);
	if (hold->path_west)
		free(hold->path_west);
	if (hold->file_name)
		free(hold->file_name);



	// free(hold);


	if (hold->img_north->img)
		mlx_destroy_image(hold->mlx, hold->img_north->img);
	if (hold->img_south->img)
		mlx_destroy_image(hold->mlx, hold->img_south->img);
	if (hold->img_east->img)
		mlx_destroy_image(hold->mlx, hold->img_east->img);
	if (hold->img_west->img)
		mlx_destroy_image(hold->mlx, hold->img_west->img);
	if (hold->img->img)
		mlx_destroy_image(hold->mlx, hold->img->img);

	if (hold->mlx_win)
		mlx_destroy_window(hold->mlx, hold->mlx_win);
	
	if (hold->img_north)
		free(hold->img_north);
	if (hold->img_south)
		free(hold->img_south);
	if (hold->img_east)
		free(hold->img_east);
	if (hold->img_west)
		free(hold->img_west);
	if (hold->img)
		free(hold->img);

	exit(0);
	return (0);
}