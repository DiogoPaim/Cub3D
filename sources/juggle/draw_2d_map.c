#include "../cub3d.h"

int	load_assets(t_mlx *mlx_p)
{
	void	**asset_arr;
	int		width;
	int		height;

	asset_arr = malloc(sizeof(void *) * 4); 
	asset_arr[0] = mlx_xpm_file_to_image(mlx_p -> mlx, 
			"./Assets/2d_floor.xpm", &width, &height);
	asset_arr[1] = mlx_xpm_file_to_image(mlx_p -> mlx, 
			"./Assets/2d_wall.xpm", &width, &height);
	asset_arr[2] = mlx_xpm_file_to_image(mlx_p -> mlx, 
			"./Assets/2d_player.xpm", &width, &height);
	asset_arr[3] = NULL; 
	mlx_p -> asset = asset_arr;
	return (1);
}

void	draw_map(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (mlx -> map[++i])
	{
		j = -1;
		while (mlx -> map[i][++j])
		{
			if (mlx->map[i][j] == '1')
				mlx_put_image_to_window(mlx->mlx,
					mlx->window, mlx->asset[1], 64 * j, 64 * i);
			else if (mlx->map[i][j] == '0')
				mlx_put_image_to_window(mlx->mlx, 
					mlx->window, mlx->asset[0], 64 * j, 64 * i);
			else if (mlx->map[i][j] == 'N' || mlx->map[i][j] == 'S' \
			|| mlx->map[i][j] == 'W' || mlx->map[i][j] == 'E')
				mlx_put_image_to_window(mlx->mlx, 
					mlx->window, mlx->asset[2], 64 * j, 64 * i);
		}
	}
}