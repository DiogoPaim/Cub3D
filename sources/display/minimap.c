/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:20:51 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/10 16:19:27 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	image_to_minimap(t_cub *cub, int asset, int x, int y)
{
	int		x_pos;
	int		y_pos;
	int		b;

	x_pos = x;
	b = x_pos;
	y_pos = y;
	if (y_pos < 0)
		y = 0;
	if (x_pos < 0)
		b = 0;
	while (y < y_pos + (cub->img[asset].h) && y < cub->img[M_MAP].h)
	{
		x = b;
		while (x < x_pos + (cub->img[asset].w) && x < cub->img[M_MAP].w)
		{
			if(x >= 0 && y >= 0)
				my_mlx_pixel_put(&cub->img[M_MAP], x, y, \
				get_color(&cub->img[asset], (x - x_pos), \
				(y - y_pos)));
			x++;
		}
		y++;
	}
}

static void	create_transparent_frame(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 128)
	{
		x = -1;
		while (++x < 128)
		{
			if ((x < 6 || x > 122) || (y < 6 || y > 122))
				put_transparent_pixel(&cub->img[M_MAP], x, y);
		}
	}
}

void	render_minimap(t_cub *cub)
{
	image_to_minimap(cub, M_BACKGROUND, 0, 0);
	image_to_minimap(cub, MAP, cub->layout.mario_x + 8 - cub->player.x * 16, cub->layout.mario_y + 8 - cub->player.y * 16);
	image_to_minimap(cub, M_MARIO, cub->layout.mario_x, cub->layout.mario_y);
	create_transparent_frame(cub);
	image_to_minimap(cub, M_LAYER, 0, 0);
	image_to_frame(cub, M_MAP, cub->layout.map_x, cub->layout.map_y);
}
