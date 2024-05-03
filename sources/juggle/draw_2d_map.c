#include "../cub3d.h"

void	draw_player(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx ,cub->window,					\
		cub->asset[PLAYER_TOP].img,									\
		(64.0 * cub->player.x) - 32, (64.0 * cub->player.y) - 32);
}

void	draw_map(t_cub *cub)
{
	int	i;
	int	j;

	i = -1;
	while ((cub->map.map)[++i])
	{
		j = -1;
		while (cub->map.map[i][++j])
		{
			if (cub->map.map[i][j] == '1')
				mlx_put_image_to_window(cub->mlx,
					cub->window, cub->asset[WALL_TOP].img, 64 * j, 64 * i);
			else if (cub->map.map[i][j] == '0')
				mlx_put_image_to_window(cub->mlx,
					cub->window, cub->asset[FLOOR_TOP].img, 64 * j, 64 * i);
		}
	}
	draw_player(cub);
	draw_line_sight_based_on_angle(cub);
}