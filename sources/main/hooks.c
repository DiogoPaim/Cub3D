/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:39:41 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/10 15:09:27 by tjorge-d         ###   ########.fr       */
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