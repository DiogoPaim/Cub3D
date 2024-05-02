/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:16:45 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/02 12:45:20 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	load_assets(t_cub *cub)
{
	int	i;

	set_asset_paths(cub);
	i = -1;
	while (++i < ASSET_NUMBER)
	{
		cub->asset[i].img = mlx_xpm_file_to_image(cub->mlx, \
			cub->asset[i].path, &cub->asset[i].w, &cub->asset[i].h);
		cub->asset[i].created = 1;
	}
}
