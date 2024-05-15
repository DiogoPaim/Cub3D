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

double get_wallX(t_cub *cub, t_ray *ray)
{
    double ans;

	if (ray->side_hit == 0)
		ans = cub->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		ans = cub->player.x + ray->perp_wall_dist * ray->dir_x;
	ans -= floor((ans));
	return (ans);
}

int coordinate_x_text(t_cub *cub, t_ray *ray, double wall_x)
{
	int tex_x;
	
	tex_x = (int) (wall_x * (double) cub->img[ray->dir_wall].w);
	if(ray->side_hit == 0 && ray->dir_x > 0)
		tex_x = cub->img[ray->dir_wall].w - tex_x - 1;
	if(ray->side_hit == 1 && ray->dir_y < 0)
		tex_x = cub->img[ray->dir_wall].w - tex_x - 1;
	return tex_x;
}
void	render_limits(t_cub *cub, int x, int c_pos, int f_pos)
{
	int	i;

	i = 0;
	while (i <= c_pos)
	{
		my_mlx_pixel_force(&cub->img[FRAME], x, i, cub->ceiling);
		i += 1 + (1 * PIXEL_SKIP);
	}
	i = (f_pos / (1 + PIXEL_SKIP) * (1 + PIXEL_SKIP));
	while (i < Y_RES)
	{
		my_mlx_pixel_force(&cub->img[FRAME], x, i, cub->floor);
		i += 1 + (1 * PIXEL_SKIP);
	}
}

void	draw_textured_line(t_ray *ray, t_cub *cub, double xy_pos_arr[3], int l_r[2])
{
	
	int				y_pos;
	int				i;
	int				normalized;
	int				y;
	double			step;

	render_limits(cub, xy_pos_arr[2], l_r[0], l_r[1]);
	normalized = ((int) l_r[0] / (1 + PIXEL_SKIP)) * (1 + PIXEL_SKIP);
	i = 0;
	step = 1.0 * cub->img[ray->dir_wall].h / (l_r[1] - l_r[0]);
	while (normalized + i <= l_r[1])
	{
		y_pos = (int)xy_pos_arr[1] & (cub->img[ray->dir_wall].h - 1);
        xy_pos_arr[1] += step;
		if (i % (PIXEL_SKIP + 1) != 0)
		{
			i ++;
			continue;
		}
		y = normalized + i;
		my_mlx_pixel_put(&cub->img[FRAME], xy_pos_arr[2], y, \
		get_color(&cub->img[ray->dir_wall], xy_pos_arr[0], y_pos));
		i += (1);
	}
}


void	render_lines(t_ray *ray, t_cub *cub, int ray_n)
{
	int			height;
	int			line_range[2];
	double		step;
	double		xy_text_pos[3];

	
	if (ray->perp_wall_dist > 0)
	{
		height = (int)(Y_RES / ray->perp_wall_dist);
		step = 1.0 * (cub->img[ray->dir_wall].h / height);
		line_range[0] = -height / 2 + Y_RES / (2);
		line_range[1] = height / 2 + Y_RES / (2);
		xy_text_pos[0] = coordinate_x_text(cub,ray,get_wallX(cub, ray));
		xy_text_pos[1] = (line_range[0] - Y_RES / 2 + height / 2) * step;
		xy_text_pos[2] = ray_n;
		draw_textured_line(ray, cub,xy_text_pos,line_range);
	}
}
      

void	barrage_of_rays(t_cub *cub)
{
	t_camera	camera;
	t_ray		ray;
	t_ray		door_ray;
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
		if(ray.door_hit)
		{
			initialize_ray(cub, &door_ray, ray_n, &camera);
			calc_delta_distance(&door_ray);
			calculate_ray_steps(&door_ray, cub);
			door_ray.perp_wall_dist = actual_dda(cub, &door_ray);
		}
		ray_n += 1 + PIXEL_SKIP;
	}
}
