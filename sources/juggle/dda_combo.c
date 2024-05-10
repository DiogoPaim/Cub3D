#include "../cub3d.h"

int get_wall_direction(t_ray *ray)
{
	if (ray->dir_y < 0 && ray->side_hit == 1)
		return (SOUTH);
	else if (ray->side_hit == 1)
		return (NORTH);
	else if (ray->dir_x > 0)
		return (EAST);
	else
		return (WEST);
}

double get_wallX(t_ray *ray)
{
    double ans;

	if (ray->side_hit == 0)
		ans = ray->y + ray->perp_wall_dist * ray->dir_y;
	else
		ans = ray->x + ray->perp_wall_dist * ray->dir_x;
	return (ans);
}

int coordinate_x_text(t_cub *cub, t_ray *ray, double wall_x)
{
	int tex_x;
	
	tex_x = (int) wall_x * (double) cub->img[ray->dir_wall].w;
	if(ray->side_hit == 0 && ray->dir_x > 0)
		tex_x = cub->img[ray->dir_wall].w - tex_x - 1;
	if(ray->side_hit == 1 && ray->dir_y < 0)
		tex_x = cub->img[ray->dir_wall].w - tex_x - 1;
	return tex_x;
}

void	render_lines(t_ray *ray, t_cub *cub, int ray_n)
{
	int	height;
	int	line_range[2];
	int	color;

	if (ray->perp_wall_dist > 0)
	{
		height = (int)(Y_RES / ray->perp_wall_dist);
		line_range[0] = -height / 2 + Y_RES / 2;
		line_range[1] = height / 2 + Y_RES / 2;
		if (line_range[0] < 0)
			line_range[0] = 0;
		if (line_range[1] >= Y_RES)
			line_range[1] = Y_RES - 1;
		if (ray->dir_wall == NORTH)
			color = 0xFF00FF;
		else if (ray->dir_wall == SOUTH)
			color = 0xFFFF00;
		else if (ray->dir_wall == EAST)
			color = 0xFF0000;
		else
			color = 0x00FF00;
		draw_vertical_line(cub, ray_n, line_range, color);
	}
}

void	barrage_of_rays(t_cub *cub)
{

	t_camera	camera;
	t_ray		ray;
	int			ray_n;

	init_camera(cub, &camera);
	ray_n = 0;
	while (ray_n < X_RES)
	{
		initialize_ray(cub, &ray, ray_n, &camera);
		calc_delta_distance(&ray);
		calculate_ray_steps(&ray, cub);
		ray.perp_wall_dist = actual_dda(cub, &ray);
		render_lines(&ray, cub, ray_n);
		ray_n += 1;
	}
}
