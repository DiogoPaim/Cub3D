#include "../cub3d.h"

void draw_vertical_line(t_cub *cub, int x, int y_range[2],int color)
{
	int i;
	int y;

	i = 0;

	while (y_range[0] + i <= y_range[1])
	{
		y = y_range[0] + i;
		mlx_pixel_put(cub->mlx, cub->window, x, y, color);
		i++;
	}
} 