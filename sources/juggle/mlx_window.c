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

int	get_max_width(char **map)
{
	int		max_width;
	int		i;

	i = -1;
	max_width = 0;
	while (map[++i])
	{
		if (ft_strlen_gnl(map[i],'\n') > max_width)
			max_width = ft_strlen_gnl(map[i],'\n');
	}
	return (max_width);
}

int	open_window_from_map_size(char **map, t_cub *cub)
{
	int	width;
	int	height;

	height = map_height(map);
	width = get_max_width(map);
	cub->window = mlx_new_window(cub->mlx, width * 64, height * 64, "Window");
	return (1);
}

int	game_close(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->window);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	cub->mlx = NULL;
	exit(0);
}
