/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:30:10 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/02 18:36:52 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	game_loop(t_cub *cub)
{
	draw_map(cub);
	update_player_mouse_angle(cub);
	return (1);
}
int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv; 
	static t_cub cub;
	
	cub_initializer(&cub);
	parser(argc, argv, &cub);
	load_cub(&cub);
	open_window_from_map_size(cub.map.map, &cub);
	mlx_hook(cub.window, 17, 0, &game_close, &cub);
	//mlx_hook(cub.window, KeyPress, KeyPressMask, &key_press, &mlx);
	mlx_loop_hook(cub.mlx, game_loop, &cub);
	mlx_loop(cub.mlx);
	free_cub(&cub, 0);
}
