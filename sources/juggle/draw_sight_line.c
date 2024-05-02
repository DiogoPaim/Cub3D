# include "../cub3d.h"

void draw_horizontal_line(t_cub *cub, float x2, float y2)
{
	int i;

	i = 0;
	if (cub->player.player_x >= x2)
	{
		while (cub->player.player_x - i >= x2)
		{
			mlx_pixel_put(cub->mlx,cub->window,(int) cub->player.player_x - i, y2, 0xFF0000);
			i++;
		}
	}
	if (cub->player.player_x < x2)
	{
		while (cub->player.player_x + i >= x2)
		{
			mlx_pixel_put(cub->mlx,cub->window,(int) cub->player.player_x + i, y2, 0xFF0000);
			i++;
		}
	}
}