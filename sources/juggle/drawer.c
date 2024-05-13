#include "../cub3d.h"

void draw_vertical_line(t_cub *cub, int x, int y_range[2],int color)
{
	int i;
	int y;
	int normalized;
	
	i = 0;
	normalized = ((int) y_range[0] / (1 + PIXEL_SKIP)) * (1 + PIXEL_SKIP);
	while (i <= normalized)
	{
		y = i;
		my_mlx_pixel_force(&cub->img[FRAME], x, y, 0);
		i += (1 + PIXEL_SKIP);
	}
	i = 0;
	while (normalized + i <= y_range[1])
	{
		y = normalized + i;
		my_mlx_pixel_force(&cub->img[FRAME], x, y, color);
		i += (1 + PIXEL_SKIP);
	}
	while (y < Y_RES)
	{
		y = normalized+ i;
		my_mlx_pixel_force(&cub->img[FRAME], x, y, 16777214);
		i += (1 + PIXEL_SKIP);
	}
} 
