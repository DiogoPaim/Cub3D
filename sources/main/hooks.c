/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:39:41 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/03 14:46:38 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == FORE)
		cub->player.y_mov++;
	else if (keycode == LEFT)
		cub->player.x_mov--;
	else if (keycode == BACK)
		cub->player.y_mov--;
	else if (keycode == RIGHT)
		cub->player.x_mov++;
	if (cub->player.x_mov == 0 && cub->player.y_mov == 0)
		cub->player.mov_angle = -1;
	else
	{
		cub->player.mov_angle = cub->player.vis_angle + \
			cub->player.mov_tool[cub->player.y_mov + 1][cub->player.y_mov + 1];
		if (cub->player.mov_angle >= 360)
			cub->player.mov_angle -= 360;
	}
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == ESC)
		game_close(cub);
	if (keycode == FORE)
		cub->player.y_mov--;
	else if (keycode == LEFT)
		cub->player.x_mov++;
	else if (keycode == BACK)
		cub->player.y_mov++;
	else if (keycode == RIGHT)
		cub->player.x_mov--;
	if (cub->player.x_mov == 0 && cub->player.y_mov == 0)
		cub->player.mov_angle = -1;
	else
	{
		cub->player.mov_angle = cub->player.vis_angle + \
			cub->player.mov_tool[cub->player.y_mov + 1][cub->player.y_mov + 1];
		if (cub->player.mov_angle >= 360)
			cub->player.mov_angle -= 360;
	}
	return (0);
}