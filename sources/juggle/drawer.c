#include "../cub3d.h"

void draw_vertical_line(t_cub *cub, int x, int y_start, int y_end)
{
	int i;
	int y;

	i = 0;

	while (y_start + i <= y_end)
	{
		y = y_start + i;
		mlx_pixel_put(cub->mlx, cub->window, x, y, 0xFFFF00);
		i++;
	}
} 