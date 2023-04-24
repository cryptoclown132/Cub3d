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