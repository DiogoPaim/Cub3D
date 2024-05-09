#include "../cub3d.h"

void barrage_of_rays(t_cub *cub)
{
	int		ray_n;
	int		height;
	int		line_range[2];
	double	distance;

	ray_n = 0;
	update_camera(cub, cub->camera);
	while (ray_n <= 1980)
	{
		distance = raycast_based_on_camera(cub, ray_n, &cub->ray);
		printf("distance == %lf\n\n", distance);
		height = WALL_HEIGHT / distance;
		line_range[0] = (-height) / 2 + Y_RES / 2;
		if (line_range[0] < 0)
			line_range[0] = 0;
		line_range[1] = height / 2 + Y_RES / 2;
		if (line_range[1] > Y_RES)
			line_range[1] = Y_RES - 1;
		if (cub->ray.side_hit == NORTHSOUTH)
			draw_vertical_line(cub, ray_n, line_range, 16711680);
		else
			draw_vertical_line(cub, ray_n, line_range, 65280);
		ray_n ++;
	}
}
void alternate_barrage(t_cub *cub)
{

	t_camera	camera;
	t_ray		ray;
	int line_range[2];
	int	i;
	int height;
	int color;
	
	// setup camera
	camera.dir_x = cos(cub->player.angle);
	camera.dir_y = sin(cub->player.angle);
	camera.fov_rad = 72 * (M_PI / 180); // Field of view in radians
	camera.plane_x = -camera.dir_y * tan(camera.fov_rad / 2);
	camera.plane_y = camera.dir_x * tan(camera.fov_rad / 2);

	i = 0;
	while (i < X_RES) //i < n_rays
	{
		// setup values for dda
		ray.x = (int)cub->player.x;
		ray.y = (int)cub->player.y;
		camera.x = 2 * i / (double)X_RES - 1;
		ray.dir_x = camera.dir_x + camera.plane_x * camera.x;
		ray.dir_y = camera.dir_y + camera.plane_y * camera.x;
		
		if (ray.dir_y == 0)
			ray.delta_d_x = INT_MAX;
		else
			ray.delta_d_x = fabs(1 / ray.dir_x);

		if (ray.dir_x == 0)
			ray.delta_d_y = INT_MAX;
		else
			ray.delta_d_y = fabs(1 / ray.dir_y);

		if (ray.dir_x < 0)
		{
			ray.step_x = -1;
			ray.side_d_x = (cub->player.x - ray.x) * ray.delta_d_x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_d_x = (ray.x + 1.0 - cub->player.x) * ray.delta_d_x;
		}
		if (ray.dir_y < 0)
		{
			ray.step_y = -1;
			ray.side_d_y = (cub->player.y - ray.y) * ray.delta_d_y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_d_y = (ray.y + 1.0 - cub->player.y) * ray.delta_d_y;
		}
		// exec dda until collision
		int hit = 0;
		while (hit == 0)
		{
			if (ray.side_d_x < ray.side_d_y)
			{
				ray.side_d_x += ray.delta_d_x;
				ray.x += ray.step_x;
				ray.side_hit = 0;
			}
			else
			{
				ray.side_d_y += ray.delta_d_y;
				ray.y += ray.step_y;
				ray.side_hit = 1;
			}
			//pixel_put(&instance->mlx_img, x, y, 0xFF0000); // check ray in 2Debug
			if (cub->map.map[ray.y][ray.x] == '1')
				hit = 1;
		}
		if (ray.side_hit == 0)
			ray.perp_wall_dist = (ray.side_d_x - ray.delta_d_x);
		else
			ray.perp_wall_dist = (ray.side_d_y - ray.delta_d_y);

		//render vertical slices from left to right
		if (ray.perp_wall_dist > 0)
		{
			height = (int)(Y_RES / ray.perp_wall_dist);
			line_range[0] = -height / 2 + Y_RES / 2;
			line_range[1] = height / 2 + Y_RES / 2;
			if (line_range[0] < 0)
				line_range[0] = 0;
			if (line_range[1] >= Y_RES)
				line_range[1] = Y_RES - 1;
			color = 16711680;
			if (ray.side_hit == 1)
				color = 65280;
			draw_vertical_line(cub, i, line_range, color);
			}
			i++;
	}
}
