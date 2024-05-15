/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:48:46 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/14 11:44:44 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	get_color(t_image *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_force(t_image *img, int x, int y, int color)
{
	char	*dst;

	if(x < 0 || y < 0 || x > X_RES || y > Y_RES)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if(x < 0 || y < 0 || x > X_RES || y > Y_RES)
		return ;
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

void	image_to_frame(t_cub *cub, t_image image, int x, int y)
{
	int		x_pos;
	int		y_pos;
	int		scale;

	x_pos = x;
	y_pos = y;
	scale = image.scale;
	if(!scale)
		scale = 1;
	while (y < y_pos + (image.h * scale) && y < Y_RES)
	{
		x = x_pos;
		while (x < x_pos + (image.w * scale) && y < X_RES)
		{
			my_mlx_pixel_put(&cub->img[FRAME], x, y, \
			get_color(&image, (x - x_pos) / scale, \
			(y - y_pos) / scale));
			x++;
		}
		y++;
	}
}
