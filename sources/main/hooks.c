/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:39:41 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/16 18:22:06 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	refresh_door(t_cub *cub)
{
	float	x;
	float	y;
	int		i;

	i = -1;
	x = cub->player.x;
	y = cub->player.y;
	while (++i <= 20)
	{
		y = y + sin((cub->player.vis_angle * 2 * M_PI) / 360) * 0.1;	
		x = x + cos((cub->player.vis_angle * 2 * M_PI) / 360) * 0.1;
		if (cub->map.map[(int)y][(int)x] == '1')
			return ;
		else if (cub->map.map[(int)y][(int)x] == '2')
		{
			cub->map.map[(int)y][(int)x] = '3';
			return ;	
		}
		else if (cub->map.map[(int)y][(int)x] == '3')
		{
			cub->map.map[(int)y][(int)x] = '2';
			return ;
		}
	}
}

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
	else if (keycode == 101 && cub->map.map[(int)(cub->player.y)]\
	[(int)(cub->player.x)] == '0')
		refresh_door(cub);
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