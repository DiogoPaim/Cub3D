/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:30:10 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/24 13:10:43 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	game_loop(t_mlx *mlx)
{
	
	mlx_hook(mlx->window, 17, 0, &game_close, mlx);
	mlx_loop(mlx -> mlx);

}
int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv; 
	//static t_cub cub;

	//cub.mlx = mlx_init();
	//cub_initializer(&cub);
	//parser(argc, argv, &cub);
	t_mlx mlx;
	mlx.map = hard_map();
	print_map(mlx.map);
	mlx.mlx = mlx_init();
	open_window_from_map_size(mlx.map, &mlx);
	game_loop(&mlx);
}
