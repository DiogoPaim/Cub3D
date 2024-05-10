/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:48:46 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/10 15:58:33 by tjorge-d         ###   ########.fr       */
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

void	put_transparent_pixel(t_image *img, int x, int y)
{
	char	*dst;
	int		color;

	color = 16777215;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	image_to_frame(t_cub *cub, int asset, int x, int y)
{
	int		x_pos;
	int		y_pos;
	int		scale;

	x_pos = x;
	y_pos = y;
	scale = cub->img[asset].scale;
	if(!scale)
		scale = 1;
	while (y < y_pos + (cub->img[asset].h * scale) && y < Y_RES)
	{
		x = x_pos;
		while (x < x_pos + (cub->img[asset].w * scale) && y < X_RES)
		{
			my_mlx_pixel_put(&cub->img[FRAME], x, y, \
			get_color(&cub->img[asset], (x - x_pos) / scale, \
			(y - y_pos) / scale));
			x++;
		}
		y++;
	}
}
