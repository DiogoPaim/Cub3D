/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:30:10 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/26 19:10:34 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		set_up_player(t_cub *cub)
{
	cub->player.player_x = cub->map.player_x;
	cub->player.player_y = cub->map.player_y; 
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
	//cub_initializer(&cub);
	//parser(argc, argv, &cub);
	
	cub.mlx = mlx_init();
	cub_initializer(&cub);
	parser(argc, argv, &cub);
	open_window_from_map_size(cub.map.map, &cub);
	load_assets(&cub);
	set_up_player(&cub);
	game_loop(&cub);
}
