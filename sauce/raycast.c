#include "../inc/cub3d.h"

void raycast(t_hold *hold, int x)
{
	int dirx = 0;
	int diry = 0;
	if (hold->cub->player_dir == 'S')
	{
		dirx = 0;
		diry = 1;
	}
	else if (hold->cub->player_dir == 'N')
	{
		dirx = 0;
		diry = -1;
	}
	else if (hold->cub->player_dir == 'E')
	{
		dirx = 1;
		diry = 0;
	}
	else if (hold->cub->player_dir == 'W')
	{
		dirx = -1;
		diry = 0;
	}
	
	double plane[2];
	plane[0] = 0;
	plane[1] = 0.66;
	//has to be implemented
	  double cameraX = 2 * x / (double)WIDHT - 1; //x-coordinate in camera space
      hold->look[0] = dirx + plane[0] * cameraX;
      hold->look[1] = diry + plane[1] * cameraX;



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
		// printf("c: %c\n", hold->cub->map[hold->map_pos[1]][hold->map_pos[0]]);
		// printf("side_dist_x: %f\nside_dist_x: %f\n", hold->side_dist[0], hold->side_dist[1]);
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
		// printf("map_pos_y = %i\n", hold->map_pos[1]);
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
