/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_painter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:48:46 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/09 17:21:52 by tjorge-d         ###   ########.fr       */
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

void paint_map_background(t_cub *cub, int asset, int width, int height)
{
	int	x;
	int	y;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			put_transparent_pixel(&cub->img[asset], x, y);
	}
}

void	render_image(t_cub *cub, int asset, int x, int y)
{
	int		x_pos;
	int		y_pos;
	int		scale;

	x_pos = x;
	y_pos = y;
	scale = cub->img[asset].scale;
	if(!scale)
		scale = 1;
	while (y < y_pos + (cub->img[asset].h * scale))
	{
		x = x_pos;
		while (x < x_pos + (cub->img[asset].w * scale))
		{
			my_mlx_pixel_put(&cub->img[FRAME], x, y, \
			get_color(&cub->img[asset], (x - x_pos) / scale, \
			(y - y_pos) / scale));
			x++;
		}
		y++;
	}
}

void	render_image_to_map(t_cub *cub, int asset, int x, int y)
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

void	create_transparent_frame(t_cub *cub)
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

void	render_map(t_cub *cub)
{
	render_image_to_map(cub, M_BACKGROUND, 0, 0);
	render_image_to_map(cub, MAP, cub->layout.mario_x + 8 - cub->player.x * 16, cub->layout.mario_y + 8 - cub->player.y * 16);
	render_image_to_map(cub, M_MARIO, cub->layout.mario_x, cub->layout.mario_y);
	create_transparent_frame(cub);
	render_image_to_map(cub, M_LAYER, 0, 0);
	render_image(cub, M_MAP, cub->layout.map_x, cub->layout.map_y);
}
