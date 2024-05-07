#include "../cub3d.h"

void barrage_of_rays(t_cub *cub)
{
	int		ray_n;
	int		height;
	int		start_line;
	int		end_line;
	// float	dir_ray[2];

	ray_n = 0;
	while (ray_n <= 3800)
	{
		height = WALL_HEIGHT / get_distance_vector_wall(cub->player.pos_v, \
			cub->player.dir_v, cub, ray_n);
		start_line = (-height) / 2 + 2060 / 2;
		if (start_line < 0)
			start_line = 0;
		end_line = height / 2 + 2060 / 2;
		if (end_line > 2060)
			end_line = 2060 - 1;
		draw_vertical_line(cub, ray_n, start_line, end_line);
		ray_n ++;
	}
}
