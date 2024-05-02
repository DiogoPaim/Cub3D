/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:50:19 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/02 17:04:29 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int player_movement(t_cub *cub)
{
    if (keyDown(SDLK_UP))
    {
        cub->player.player_x = cub->player.player_x + cos(cub->player.player_vison_angle) * SPEED;
        cub->player.player_y = cub->player.player_y - sin(cub->player.player_vison_angle) * SPEED;
    }
    if (keyDown(SDLK_DOWN))
    {
      return(1);
    }
    if (keyDown(SDLK_RIGHT))
    {
      return(1);
    }
}