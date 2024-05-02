/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:50:19 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/02 18:26:52 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int player_movement(t_cub *cub)
{
	cub->player.x = cub->player.x + cos(cub->player.mov_angle) * SPEED;
	cub->player.y = cub->player.y - sin(cub->player.mov_angle) * SPEED;
	return(1);
}