#include "../cub3d.h"

void	draw_player(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx ,cub->window,					\
		cub->asset[PLAYER_TOP].img,									\
		(64.0 * cub->player.player_x) - 32, (64.0 * cub->player.player_y) - 32);
}

void	 draw_map(t_cub *cub)
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
	if((cub->player.player_vison_angle >= 45 && cub->player.player_vison_angle < 135)
		|| (cub->player.player_vison_angle >= 225 && cub->player.player_vison_angle < 315))
		draw_vertical_line(cub, cub->player.player_x , 0 );
	else
		draw_horizontal_line(cub, 0 , cub->player.player_y);
}