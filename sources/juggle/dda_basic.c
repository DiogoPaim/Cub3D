#include "../cub3d.h"


// double	calc_dist(t_cub *cub, double s_dist_xy[2], double delta_xy[2])
// {
// 	if(cub->ray_side_hit == 0) 
// 		return (s_dist_xy[0] - delta_xy[0]);
//     else
// 		return (s_dist_xy[1] - delta_xy[1]);
// }

double calculate_dist(t_ray *ray)
{
	if (ray->side_hit == 0)
	{
		printf("HERE 4\n");
		return (ray->side_d_x - ray->delta_d_x);
	}
	else
	{
		printf("HERE 4\n");
		return (ray->side_d_y - ray->delta_d_y);
	}
}

// double	dda_main(double s_dist_xy[2], double delta_xy[2], int step_xy[2] , t_cub *cub)
// {
// 	int map_x;
// 	int map_y;
// 	int hit;

// 	hit = 0;
// 	map_x = (int) cub->player.x;
// 	map_y = (int) cub->player.y;
// 	while (!hit)
// 	{
// 		if(s_dist_xy[0] < s_dist_xy[1])
// 		{
// 			s_dist_xy[0] += delta_xy[0];
// 			map_x += step_xy[0];
// 			cub->ray_side_hit = NORTHSOUTH;
// 		}
// 		else
// 		{
// 			s_dist_xy[1] += delta_xy[1];
// 			map_y += step_xy[1];
// 			cub->ray_side_hit = WESTEAST;
// 		}
// 		if (cub->map.map[map_y][map_x] && cub->map.map[map_y][map_x] == '1')
// 			hit = 1;
// 	}
// 	return calc_dist(cub, s_dist_xy, delta_xy);
// }

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

void	calculate_ray_steps(t_ray *ray, t_cub *cub)
{
	if(ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_d_x = (cub->player.x - ray->x) * ray->delta_d_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_d_x = ((ray->x + 1) - cub->player.x) * ray->delta_d_x;
	}
	if(ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_d_y = (cub->player.y - ray->y) * ray->delta_d_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_d_y = ((ray->y + 1) - cub->player.y) * ray->delta_d_y;
	}
}

void	calc_delta_distance(t_ray *ray)
{
	if (ray->dir_x != 0)
		ray->delta_d_x = fabs(1 / ray->dir_x);
	else 
		ray->delta_d_x = INT_MAX;
	if (ray->dir_y != 0)
		ray->delta_d_y = fabs(1 / ray->dir_y);
	else
		ray->delta_d_y = INT_MAX;
}

double	actual_dda(t_cub *cub, t_ray *ray)
{
	int hit;

	hit = 0;
	while (!hit)
	{
		if(ray->side_d_x < ray->side_d_y)
		{
			ray->side_d_x += ray->delta_d_x;
			ray->x +=  ray->step_x;
			ray->side_hit = NORTHSOUTH;
		}
		else
		{
			ray->side_d_y += ray->delta_d_y;
			ray->y += ray->step_y;
			ray->side_hit = WESTEAST;
		}
		printf("HERE 5");
		printf(" map char is =%c\n",cub->map.map[ray->y][ray->x]);
		if (cub->map.map[ray->y][ray->x] \
		&& cub->map.map[ray->y][ray->x] == '1')
			hit = 1;
	}
	return calculate_dist(ray);
}

double	raycast_based_on_camera(t_cub *cub, int ray_n , t_ray *ray)
{
	cub->camera.x = (2 * ray_n) / (double) X_RES - 1;
	ray->x = (int) cub->player.x;
	ray->y = (int) cub->player.y;
	ray->dir_x = cub->player.x + (cub->camera.plane_x * cub->camera.x);
	ray->dir_y = cub->player.y + (cub->camera.plane_y * cub->camera.x);
	calc_delta_distance(ray);
	calculate_ray_steps(ray, cub);
	return (actual_dda(cub, ray));
}
// double get_distance_vector_wall(float pos_v[2], float dir_v[2], \
// 	t_cub *cub, int i)
// {
// 	double	side_dist_xy[2];
// 	double	delta_dist_xy[2];
// 	int		step_xy[2];

// 	cub->camera.x = (2 * i) / (double) X_RES - 1;
// 	draw_line_sight_based_on_angle(cub);
// 	dir_v[0] = dir_v[0] + (cub->camera.plane_x * cub->camera.x);
// 	dir_v[1] = dir_v[1] + (cub->camera.plane_y * cub->camera.x);
// 	if (dir_v[0] != 0)
// 		delta_dist_xy[0] = fabs(1 / dir_v[0]);
// 	else 
// 		delta_dist_xy[0] = INT_MAX;
// 	if (dir_v[1] != 0)
// 		delta_dist_xy[1] = fabs(1 / dir_v[1]);
// 	else
// 		delta_dist_xy[1] = INT_MAX;
// 	if( dir_v[0] < 0)
// 		step_side_neg(&step_xy[0],&side_dist_xy[0],pos_v[0], delta_dist_xy[0]);
// 	else
// 		step_side_pos(&step_xy[0],&side_dist_xy[0],pos_v[0], delta_dist_xy[0]);
// 	if(dir_v[1] < 0)
// 		step_side_neg(&step_xy[1],&side_dist_xy[1],pos_v[1], delta_dist_xy[1]);
// 	else 
// 		step_side_pos(&step_xy[1],&side_dist_xy[1],pos_v[1], delta_dist_xy[1]);
// 	return dda_main(side_dist_xy, delta_dist_xy, step_xy, cub);
// }
