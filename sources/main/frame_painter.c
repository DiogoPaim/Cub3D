/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_painter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:48:46 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/07 18:28:14 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	get_color(t_image *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (color == TRANSPARENT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_image(t_cub *cub, int asset, int x, int y)
{
	int		x_pos;
	int		y_pos;

	x_pos = x;
	y_pos = y;
	while (y < y_pos + cub->asset[asset].h)
	{
		x = x_pos;
		while (x < x_pos + cub->asset[asset].h)
		{
			my_mlx_pixel_put(&cub->frame, x, y, \
			get_color(&cub->asset[asset], x - x_pos, y - y_pos));
			x++;
		}
		y++;
	}
}

void	render_frame(t_cub *cub)
{
	render_image(cub, M_MARIO, cub->player.x, cub->player.y);
	render_image(cub, MAP, X_RES - MAP_OFFSET - MAP_SIZE, MAP_OFFSET);
	render_image(cub, M_GOOMBA, X_RES - MAP_OFFSET - MAP_SIZE + 50, MAP_OFFSET + 50);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->frame.img, 0, 0);
	return ;
}
