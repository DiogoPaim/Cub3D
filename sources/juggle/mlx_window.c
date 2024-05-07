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

int	open_window_4k(t_cub *cub)
{
	cub->window = mlx_new_window(cub->mlx, X_RES, Y_RES, "Window");
	mlx_mouse_move(cub->mlx, cub->window, 1920, 1080);
	return (1);
}

void update_player_mouse_angle(t_cub *cub)
{
	int x;
	int y;
	
	mlx_mouse_get_pos(cub->mlx, cub->window, &x, &y);
	cub->player.vis_angle += (x - 1920)/SENSITIVITY;
	mlx_mouse_move(cub->mlx, cub->window, 1920, 1080);
	if (cub->player.vis_angle >=  360.0)
	{cub->player.vis_angle = cub->player.vis_angle - (360.0/cub->player.vis_angle)*360.0;}
	else if(cub->player.vis_angle < 0.0)
	cub->player.vis_angle += 360;
}

int	game_close(t_cub *cub)
{
	mlx_do_key_autorepeaton(cub->mlx);
	mlx_destroy_window(cub->mlx, cub->window);
	free_cub(cub, 0);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(0);
}
