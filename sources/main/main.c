/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:30:10 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/08 19:14:00 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	game_loop(t_cub *cub)
{
	gettimeofday(&cub->time, NULL);
	if ((cub->time.tv_sec * 1000000 + \
	cub->time.tv_usec) > cub->last_frame)
	{
		paint_screen_black(cub);
		player_movement(cub);
		update_player_mouse_angle(cub);
		//draw_map(cub);
		//render_frame(cub);
		barrage_of_rays(cub);
		mlx_put_image_to_window(cub->mlx, cub->window, cub->img[FRAME].img, 0, 0);
		gettimeofday(&cub->time, NULL);
		cub->last_frame = cub->time.tv_sec * 1000000 \
		+ cub->time.tv_usec + (1000000 / FRAME_RATE);
	}
	return (1);
}
int	main(int argc, char **argv)
{
	(void) 			argc;
	(void) 			argv; 
	static t_cub	cub;
	
	cub_initializer(&cub);
	parser(argc, argv, &cub);
	load_cub(&cub);
	open_window_4k(&cub);
	mlx_mouse_move(cub.mlx, cub.window, X_RES/2, Y_RES/2);
	mlx_hook(cub.window, 17, StructureNotifyMask, &game_close, &cub.mlx);
	mlx_hook(cub.window, KeyPress, KeyPressMask, &key_press, &cub.mlx);
	mlx_hook(cub.window, KeyRelease, KeyReleaseMask, &key_release, &cub.mlx);
	mlx_loop_hook(cub.mlx, game_loop, &cub);
	mlx_loop(cub.mlx);
	free_cub(&cub, 0);
}
