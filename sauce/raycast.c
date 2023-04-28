#include "../inc/cub3d.h"

void raycast(t_hold *hold, int x)
{

	//has to be implemented
	double cameraX = 2 * x / (double)WIDHT - 1; //x-coordinate in camera space
	hold->look[0] = hold->dirx + hold->plane[0] * cameraX;
	hold->look[1] = hold->diry + hold->plane[1] * cameraX;


	if(hold->look[0] == 0)
	{
		hold->delta_dist[0] = 999999999999999;
	}
	else
	{
		hold->delta_dist[0] = fabsf(1/ hold->look[0]);
	}
	if(hold->look[1] == 0)
	{
		hold->delta_dist[1] = 999999999999999;
	}
	else
	{
		hold->delta_dist[1] = fabsf(1/ hold->look[1]);
	}

	// side dist for x
	if (hold->look[0] < 0)
	{
		hold->step[0] = -1;
		hold->side_dist[0] = (hold->pos[0] - hold->map_pos[0]) * hold->delta_dist[0];
	}
	else
	{
		hold->step[0] = 1;
		hold->side_dist[0] = (hold->map_pos[0] + 1.0 - hold->pos[0]) * hold->delta_dist[0];
	}

	// same for y
	if (hold->look[1] < 0)
	{
		hold->step[1] = -1;
		hold->side_dist[1] = (hold->pos[1] - hold->map_pos[1]) * hold->delta_dist[1];
	}
	else
	{
		hold->step[1] = 1;
		hold->side_dist[1] = (hold->map_pos[1] + 1.0 - hold->pos[1]) * hold->delta_dist[1];
	}
	dda(hold);
}


void dda(t_hold *hold)
{
	// printf("ok\n");
	hold->map_pos[0] = (int)hold->pos[0];//change value 
	hold->map_pos[1] = (int)hold->pos[1];
	// 	exit(0);
	int i = 0;
	while (1)
	{
		// printf("i = %i\n", i);
		if (hold->side_dist[0] < hold->side_dist[1])
		{
			hold->side_dist[0] += hold->delta_dist[0];
			hold->map_pos[0] += hold->step[0];
			hold->side = 0;
		}
		else
		{
			hold->side_dist[1] += hold->delta_dist[1];
			hold->map_pos[1] += hold->step[1];
			hold->side = 1;
		}
		if (hold->cub->map[hold->map_pos[1]][hold->map_pos[0]] == '1')
		{
			// printf("hit wall\n");
			// exit(0);
			break;
		}
		i++;
	}
	if (hold->side == 0)
	{
		hold->wall_dist = hold->side_dist[0] - hold->delta_dist[0];
	}
	else
		hold->wall_dist = hold->side_dist[1] - hold->delta_dist[1];

	hold->cub->line_height = (int)(HEIGHT / hold->wall_dist);
	hold->cub->tex_start = -hold->cub->line_height / 2 + HEIGHT / 2;
	// hold->cub->tex_start = hold->cub->line_height / 2 + HEIGHT / 2;
	if (hold->cub->tex_start < 0)
		hold->cub->tex_start = 0;
	hold->cub->tex_end = hold->cub->line_height / 2 + HEIGHT / 2;
	if (hold->cub->tex_end >= HEIGHT)
		hold->cub->tex_end = HEIGHT - 1;
}
