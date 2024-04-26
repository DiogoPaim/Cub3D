#include "../cub3d.h"

int	load_assets(t_cub *cub)
{
	int		width;
	int		height;


	cub->asset[FLOOR_TOP].img = mlx_xpm_file_to_image(cub -> mlx, 
			"./Assets/2d_floor.xpm", &width, &height);
	cub->asset[WALL_TOP].img = mlx_xpm_file_to_image(cub -> mlx, 
			"./Assets/2d_wall.xpm", &width, &height);
	cub->asset[PLAYER_TOP].img = mlx_xpm_file_to_image(cub -> mlx, 
			"./Assets/2d_player.xpm", &width, &height);
	return (1);
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
			else if (cub->map.map[i][j] == 'N' || cub->map.map[i][j] == 'S' \
			|| cub->map.map[i][j] == 'W' || cub->map.map[i][j] == 'E')
				mlx_put_image_to_window(cub->mlx,
					cub->window, cub->asset[PLAYER_TOP].img, 64 * j, 64 * i);
		}
	}
}