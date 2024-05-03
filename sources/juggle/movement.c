/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:50:19 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/03 14:43:24 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int player_movement(t_cub *cub)
{
	if (cub->player.mov_angle >= 0)
	{
		cub->player.y = cub->player.y + (sin((cub->player.mov_angle * 2 * 3.141592) / 360) * SPEED);	
		cub->player.x = cub->player.x + (cos((cub->player.mov_angle * 2 * 3.141592) / 360) * SPEED);
		printf("\nx: %fy: %f\n", cub->player.x, cub->player.y);
	}
	return(1);
}