/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:50:19 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/03 15:33:04 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int player_movement(t_cub *cub)
{
	if (cub->player.x_mov == 0 && cub->player.y_mov == 0)
		cub->player.mov_angle = -1;
	else
	{
		cub->player.mov_angle = cub->player.vis_angle + \
			cub->player.mov_tool[cub->player.y_mov + 1][cub->player.x_mov + 1];
		if (cub->player.mov_angle >= 360)
			cub->player.mov_angle -= 360;
	}
	if (cub->player.mov_angle >= 0)
	{
		cub->player.y = cub->player.y + \
			sin((cub->player.mov_angle * 2 * 3.141592) / 360) * SPEED;	
		cub->player.x = cub->player.x + \
			cos((cub->player.mov_angle * 2 * 3.141592) / 360) * SPEED;
	}
	return(1);
}