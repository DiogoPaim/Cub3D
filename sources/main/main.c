/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:30:10 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/24 11:58:09 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_assets(t_cub *cub)
{
	if (cub->asset[N].created)
		mlx_destroy_image(cub->mlx, cub->asset[N].img);
	if (cub->asset[S].created)
		mlx_destroy_image(cub->mlx, cub->asset[N].img);
	if (cub->asset[W].created)
		mlx_destroy_image(cub->mlx, cub->asset[N].img);
	if (cub->asset[E].created)
		mlx_destroy_image(cub->mlx, cub->asset[N].img);
}

void	free_cub(t_cub *cub, int exit_code)
{
	free_assets(cub);
	exit(exit_code);
}

void	cub_initializer(t_cub *cub)
{
	static t_img	asset[4];
	static t_map	map;
	static t_frame	frame;
	
	asset[N]
	cub->asset = asset;
	cub->map = map;
	cub->frame = frame;
}

int	main(int argc, char **argv)
{
	static t_cub cub;

	cub_initializer(&cub);
	parser(argc, argv, &cub);
}
