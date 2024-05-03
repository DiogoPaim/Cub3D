/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:39:41 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/03 11:10:46 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == FORE)
		cub->player.front_mov++;
	else if (keycode == LEFT)
		cub->player.side_mov--;
	else if (keycode == BACK)
		cub->player.front_mov--;
	else if (keycode == RIGHT)
		cub->player.side_mov++;
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == 65307)
		game_close(cub);
	if (keycode == FORE)
		cub->player.front_mov--;
	else if (keycode == LEFT)
		cub->player.side_mov++;
	else if (keycode == BACK)
		cub->player.front_mov++;
	else if (keycode == RIGHT)
		cub->player.side_mov--;
	return (0);
}