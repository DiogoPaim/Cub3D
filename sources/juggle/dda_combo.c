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
		
		distance = get_distance_vector_wall(cub->player.pos_v, \
			cub->player.dir_v, cub, ray_n);
		height = WALL_HEIGHT / distance;
		line_range[0] = (-height) / 2 + Y_RES / 2;
		if (line_range[0] < 0)
			line_range[0] = 0;
		line_range[1] = height / 2 + Y_RES / 2;
		if (line_range[1] > Y_RES)
			line_range[1] = Y_RES - 1;
		if(cub->ray_side_hit == NORTHSOUTH)
			draw_vertical_line(cub, ray_n, line_range, 0xFF0000);
		else
			draw_vertical_line(cub, ray_n, line_range, 0x00FF00);
		ray_n ++;
	}
}
