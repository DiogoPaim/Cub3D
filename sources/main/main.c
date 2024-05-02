/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:30:10 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/02 12:59:00 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_up_player(t_cub *cub)
{
	cub->player.player_x = (cub->map.player_x + 0.5);
	cub->player.player_y = (cub->map.player_y + 0.5); 
	if(cub->map.player_dir == 'N')
		cub->player.player_vison_angle = 90.0;
	else if(cub->map.player_dir == 'S')
		cub->player.player_vison_angle = 270.0;
	else if(cub->map.player_dir == 'E')
		cub->player.player_vison_angle = 0.0;
	else if(cub->map.player_dir == 'W')
		cub->player.player_vison_angle = 180.0;
	cub->player.height = 1;
}

void	game_loop(t_cub *cub)
{
	mlx_hook(cub-> window, 17, 0, &game_close, cub);
	draw_map(cub);
	mlx_loop(cub -> mlx);
}
int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv; 
	static t_cub cub;
	
	cub_initializer(&cub);
	parser(argc, argv, &cub);
	load_assets(&cub);
	open_window_from_map_size(cub.map.map, &cub);
	set_up_player(&cub);
	game_loop(&cub);
	free_cub(&cub, 0);
}
