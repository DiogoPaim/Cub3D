/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:20:02 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/08 16:01:47 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_mov_tool(t_cub *cub)
{
	cub->player.mov_tool[0][1] = 0;
	cub->player.mov_tool[0][2] = 45;
	cub->player.mov_tool[1][2] = 90;
	cub->player.mov_tool[2][2] = 135;
	cub->player.mov_tool[2][1] = 180;
	cub->player.mov_tool[2][0] = 225;
	cub->player.mov_tool[1][0] = 270;
	cub->player.mov_tool[0][0] = 315;
	cub->player.mov_tool[1][1] = -1;
}

void	set_layout(t_cub *cub)
{
	cub->layout.border_size = (X_RES + Y_RES) / 2 / 30;
	cub->layout.map_size = 128 * cub->img[MAP].scale;
	cub->layout.map_x = X_RES - cub->layout.border_size - cub->layout.map_size;
	cub->layout.map_y = cub->layout.border_size;
	cub->layout.mario_x = 128 / 2 - (16/2);
	cub->layout.mario_y = 128 / 2 - (16/2);
}

void	cub_initializer(t_cub *cub)
{
	static t_image			img[ASSET_NUMBER + 3];
	static t_map			map;
	static t_player			player;
	static char				*arg[6];
	
	cub->img = img;
	cub->map = map;
	cub->player = player;
	cub->arg = arg;
	cub->planeX = 0;
	cub->planeY = 0.66;
	set_mov_tool(cub);
	set_layout(cub);
    (void)cub;
}