/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:20:02 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/24 17:55:44 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void set_asset_paths(t_cub *cub)
{
	cub->arg[0] = NULL;
	cub->arg[1] = NULL;
	cub->arg[2] = NULL;
	cub->arg[3] = NULL;
    (void)cub;
}

void	cub_initializer(t_cub *cub)
{
	static t_image	asset[ASSET_NUMBER];
	static t_map	map;
	static t_frame	frame;
	
	set_asset_paths(cub);
	cub->asset = asset;
	cub->map = map;
	cub->frame = frame;
    (void)cub;
}