#include "../cub3d.h"

void	step_side_pos(int *step, double *step_dist, double pos, double delta)
{
	*step = 1;
	*step_dist = (((int) pos + 1) - pos) * delta;
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

double get_distance_vector_wall(float pos_v[2], float dir_v[2], \
	t_cub *cub, int i)
{
	double	side_dist_xy[2];
	double	delta_dist_xy[2];
	int		step_xy[2];

	cub->camera.x = (2 * i) / (double) X_RES - 1;
	draw_line_sight_based_on_angle(cub);
	// printf("before ray_dir_x == %lf \n",dir_v[0]);
	// printf("before ray_dir_y == %lf \n/n",dir_v[1]);
	dir_v[0] = dir_v[0] + (cub->camera.plane_x * cub->camera.x);
	dir_v[1] = dir_v[1] + (cub->camera.plane_y * cub->camera.x);
	// printf("after ray_dir_x == %lf \n",dir_v[0]);
	// printf("after ray_dir_y == %lf \n/n",dir_v[1]);
	// printf("plane_x == %lf \n", cub->camera.plane_x);
	// printf("plane_y == %lf \n", cub->camera.plane_y);
	// printf("i == %d \n", i);
	// printf("camera_x == %lf \n", cub->camera.x);
	if (dir_v[0] != 0)
		delta_dist_xy[0] = fabs(1 / dir_v[0]);
	else 
		delta_dist_xy[0] = INT_MAX;
	if (dir_v[1] != 0)
		delta_dist_xy[1] = fabs(1 / dir_v[1]);
	else
		delta_dist_xy[1] = INT_MAX;
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
