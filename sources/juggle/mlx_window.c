#include "../cub3d.h"

int	map_height(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
		i++;
	return (i);
}
int	ft_strlen_gnl(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}
int	open_window_from_map_size(char **map, t_mlx *mlx)
{
	int	width;
	int	height;

	height = map_height(map);
	width = ft_strlen_gnl(map[0], '\n');
	mlx -> window = mlx_new_window(mlx -> mlx, width * 64, height * 64, "Window");
	return (1);
}

int	game_close(t_mlx *mlx)
{
	mlx_destroy_window(mlx -> mlx, mlx -> window);
	mlx_destroy_display(mlx -> mlx);
	free(mlx->mlx);
	mlx->mlx = NULL;
	exit(1);
}
