/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:20:02 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/07 17:33:22 by tjorge-d         ###   ########.fr       */
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

void	cub_initializer(t_cub *cub)
{
	static t_image			asset[ASSET_NUMBER];
	static t_map			map;
	static t_player			player;
	static t_image			frame;
	static struct timeval	time;
	static char				*arg[6];
	
	cub->asset = asset;
	cub->map = map;
	cub->player = player;
	cub->frame = frame;
	cub->time = time;
	cub->arg = arg;
	cub->planeX = 0;
	cub->planeY = 0.66;
	set_mov_tool(cub);
    (void)cub;
}