#include "../inc/cub3d.h"

void raycast(t_hold *hold, int x)
{
	double cameraX = 2 * x / (double)WIDHT - 1;
	hold->look[0] = hold->dirx + hold->plane[0] * cameraX;
	hold->look[1] = hold->diry + hold->plane[1] * cameraX;
	if(hold->look[0] == 0)
	{
		hold->delta_dist[0] = 1e30;
	}
	else
	{
		hold->delta_dist[0] = fabs(1/ hold->look[0]);
	}
	if(hold->look[1] == 0)
	{
		hold->delta_dist[1] = 1e30;
	}
	else
	{
		hold->delta_dist[1] = fabs(1/ hold->look[1]);
	}

	hold->map_pos[0] = (int)hold->pos[0]; 
	hold->map_pos[1] = (int)hold->pos[1];
	
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
	int i = 0;
	while (1)
	{
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
		if (hold->map[hold->map_pos[1]][hold->map_pos[0]] == '1')
		{
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
	
	hold->line_height = (int)(HEIGHT / hold->wall_dist);
	hold->tex_start = -hold->line_height / 2 + HEIGHT / 2;

	if (hold->tex_start < 0)
		hold->tex_start = 0;
	hold->tex_end = hold->line_height / 2 + HEIGHT / 2;
	if (hold->tex_end >= HEIGHT)
		hold->tex_end = HEIGHT - 1;
}
