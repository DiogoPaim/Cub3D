# include "../cub3d.h"

void draw_horizontal_line(t_cub *cub, float x2, float y2)
{
	int i;
	int x;
	int y;

	i = 0;
	if (cub->player.player_x >= x2)
	{
		while ((cub->player.player_x*64) - i >= x2)
		{
			x = (int) (cub->player.player_x*64) - i;
			y = y2 * 64;
			mlx_pixel_put(cub->mlx,cub->window,x, y, 0xFF0000);
			i++;
		}
	}
	if ((cub->player.player_x*64) < x2)
	{
		while (cub->player.player_x + i < x2)
		{
			x = (int) (cub->player.player_x*64) + i;
			y = y2 * 64;
			mlx_pixel_put(cub->mlx,cub->window,x, y, 0xFF0000);
			i++;
		}
	}
}