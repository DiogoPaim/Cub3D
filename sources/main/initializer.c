/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:20:02 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/03 11:12:06 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cub_initializer(t_cub *cub)
{
	static t_image	asset[ASSET_NUMBER];
	static t_map	map;
	static t_frame	frame;
	static char		*arg[6];
	
	cub->asset = asset;
	cub->map = map;
	cub->frame = frame;
	cub->arg = arg;
    (void)cub;
}