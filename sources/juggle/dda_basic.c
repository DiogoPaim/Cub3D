#include "../cub3d.h"

void	step_side_pos(int *step, double *step_dist, double pos, double delta)
{
	*step = 1;
	*step_dist = (((int) pos + 1 ) - pos) * delta;
}
void	step_side_neg(int *step, double *step_dist, double pos, double delta)
{
	*step = -1;
	*step_dist = (pos - (int)pos) * delta;
}

double	calc_dist(t_cub *cub, double s_dist_xy[2], double delta_xy[2])
{
	if(cub->ray_side_hit == 0) 
		return (s_dist_xy[0] - delta_xy[0]);
    else
		return (s_dist_xy[1] - delta_xy[1]);
}

double	dda_main(double s_dist_xy[2], double delta_xy[2], int step_xy[2] , t_cub *cub)
{
	int map_x;
	int map_y;
	int hit;

	hit = 0;
	map_x = (int) cub->player.x;
	map_y = (int) cub->player.y;
	while (!hit)
	{
		if(s_dist_xy[0] < s_dist_xy[1])
		{
			s_dist_xy[0] += delta_xy[0];
			map_x += step_xy[0];
			cub->ray_side_hit = NORTHSOUTH;
		}
		else
		{
			s_dist_xy[1] += delta_xy[1];
			map_y += step_xy[1];
			cub->ray_side_hit = WESTEAST;
		}
		if (cub->map.map[map_y][map_x] && cub->map.map[map_y][map_x] == '1')
			hit = 1;
	}
	return calc_dist(cub, s_dist_xy, delta_xy);
}

double get_distance_vector_wall(float pos_v[2], float dir_v[2], t_cub *cub, \
	int camera_ray)
{
	double	side_dist_xy[2];
	double	delta_dist_xy[2];
	int		step_xy[2];
	(void) camera_ray;
	double camera_x = 2 * camera_ray / (1900 - 1);
	dir_v[0] = dir_v[0] + cub->planeX * camera_x;
	dir_v[1] = dir_v[1] + cub->planeY * camera_x;
	if (dir_v[0] != 0)
		delta_dist_xy[0] = sqrt(1 + (dir_v[1] * dir_v[1]) / (dir_v[0] * dir_v[0]));
	else 
		delta_dist_xy[0] = DBL_MAX;
	if (dir_v[1] != 0)
		delta_dist_xy[1] = sqrt(1 + (dir_v[0] * dir_v[0]) / (dir_v[1] * dir_v[1]));
	else
		delta_dist_xy[1] = DBL_MAX;
	if( dir_v[0] < 0)
		step_side_neg(&step_xy[0],&side_dist_xy[0],pos_v[0], delta_dist_xy[0]);
	else
		step_side_pos(&step_xy[0],&side_dist_xy[0],pos_v[0], delta_dist_xy[0]);
	if(dir_v[1] < 0)
		step_side_neg(&step_xy[1],&side_dist_xy[1],pos_v[1], delta_dist_xy[1]);
	else 
		step_side_pos(&step_xy[1],&side_dist_xy[1],pos_v[1], delta_dist_xy[1]);
	return dda_main(side_dist_xy, delta_dist_xy, step_xy, cub);
}
