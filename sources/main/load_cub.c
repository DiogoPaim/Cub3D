/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:16:45 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/09 11:20:43 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_up_player(t_cub *cub)
{
	cub->player.x = (cub->map.player_x + 0.5);
	cub->player.y = (cub->map.player_y + 0.5); 
	cub->player.mov_angle = -1;
	if(cub->map.player_dir == 'N')
		cub->player.vis_angle = 270.0;
	else if(cub->map.player_dir == 'S')
		cub->player.vis_angle = 90.0;
	else if(cub->map.player_dir == 'E')
		cub->player.vis_angle = 0.0;
	else if(cub->map.player_dir == 'W')
		cub->player.vis_angle = 180.0;
	cub->player.height = 1;
	cub->player.angle = cub->player.vis_angle * (M_PI/180);
}

static void	set_asset_paths(t_cub *cub)
{
	cub->img[N].path = cub->arg[N];
	cub->img[S].path = cub->arg[S];
	cub->img[W].path = cub->arg[W];
	cub->img[E].path = cub->arg[E];
	cub->img[FLOOR_TOP].path = "./Assets/2d_floor.xpm";
	cub->img[WALL_TOP].path = "./Assets/2d_wall.xpm";
	cub->img[PLAYER_TOP].path = "./Assets/2d_player.xpm";
	cub->img[M_MAP].path = "./Assets/minimap2.xpm";
	cub->img[M_LAYER].path = "./Assets/mini_layer2.xpm";
	cub->img[M_WALL].path = "./Assets/mini_wall.xpm";
	cub->img[M_MARIO].path = "./Assets/mini_mario.xpm";
	cub->img[M_GOOMBA].path = "./Assets/mini_goomba.xpm";
	cub->img[M_MUSHROOM].path = "./Assets/mini_mushroom.xpm";
    (void)cub;
}

void	load_cub(t_cub *cub)
{
	int	i;

	cub->mlx = mlx_init();
	mlx_do_key_autorepeatoff(cub->mlx);
	set_up_player(cub);
	init_camera(cub);
	set_asset_paths(cub);
	gettimeofday(&cub->time, NULL);
	cub->last_frame = cub->time.tv_sec * 1000000 \
		+ cub->time.tv_usec;
	i = -1;
	while (++i < ASSET_NUMBER + IMG_NUMBER)
	{
		if (i >= ASSET_NUMBER)
			cub->img[i].img = mlx_new_image(cub->mlx, cub->img[i].w, cub->img[i].h);
		else
			cub->img[i].img = mlx_xpm_file_to_image(cub->mlx, \
				cub->img[i].path, &cub->img[i].w, &cub->img[i].h);
		cub->img[i].addr = mlx_get_data_addr(cub->img[i].img, \
			&cub->img[i].bpp, &cub->img[i].line_length, &cub->img[i].endian);
		cub->img[i].created = 1;
	}
	paint_map_background(cub);
	
}
