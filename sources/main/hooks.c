/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:39:41 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/14 12:58:07 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == FORE)
		cub->player.y_mov--;
	else if (keycode == LEFT)
		cub->player.x_mov--;
	else if (keycode == AFT)
		cub->player.y_mov++;
	else if (keycode == RIGHT)
		cub->player.x_mov++;
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == ESC)
		game_close(cub, 2);
	if (keycode == FORE)
		cub->player.y_mov++;
	else if (keycode == LEFT)
		cub->player.x_mov++;
	else if (keycode == AFT)
		cub->player.y_mov--;
	else if (keycode == RIGHT)
		cub->player.x_mov--;
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if(!cub->player.shooting && keycode == 1)
			cub->player.shooting = 1;
	return (0);
}