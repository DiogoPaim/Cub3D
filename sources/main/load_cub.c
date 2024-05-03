/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:16:45 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/03 14:18:57 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_up_player(t_cub *cub)
{
	cub->player.x = (cub->map.player_x + 0.5);
	cub->player.y = (cub->map.player_y + 0.5); 
	cub->player.mov_angle = -1;
	if(cub->map.player_dir == 'N')
		cub->player.vis_angle = 90.0;
	else if(cub->map.player_dir == 'S')
		cub->player.vis_angle = 270.0;
	else if(cub->map.player_dir == 'E')
		cub->player.vis_angle = 0.0;
	else if(cub->map.player_dir == 'W')
		cub->player.vis_angle = 180.0;
	cub->player.height = 1;
}

static void	set_asset_paths(t_cub *cub)
{
	cub->asset[N].path = cub->arg[N];
	cub->asset[S].path = cub->arg[S];
	cub->asset[W].path = cub->arg[W];
	cub->asset[E].path = cub->arg[E];
	cub->asset[FLOOR_TOP].path = "./Assets/2d_floor.xpm";
	cub->asset[WALL_TOP].path = "./Assets/2d_wall.xpm";
	cub->asset[PLAYER_TOP].path = "./Assets/2d_player.xpm";
    (void)cub;
}

void	load_cub(t_cub *cub)
{
	int	i;

	cub->mlx = mlx_init();
	mlx_do_key_autorepeatoff(cub->mlx);
	set_up_player(cub);
	set_asset_paths(cub);
	i = -1;
	while (++i < ASSET_NUMBER)
	{
		cub->asset[i].img = mlx_xpm_file_to_image(cub->mlx, \
			cub->asset[i].path, &cub->asset[i].w, &cub->asset[i].h);
		cub->asset[i].created = 1;
	}
}
