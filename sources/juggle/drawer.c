#include "../cub3d.h"

void draw_vertical_line(t_cub *cub, int x, int y_range[2],int color)
{
	int i;
	int y;
	int normalized;
	i = 0;

	normalized  = (int) y_range[0] / 1;

	while (normalized*1 + i <= y_range[1])
	{
		y = normalized*1 + i;
		my_mlx_pixel_put(&cub->img[FRAME], x, y, color);
		i++;
	}
} 