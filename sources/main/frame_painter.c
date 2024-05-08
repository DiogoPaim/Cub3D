/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_painter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:48:46 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/08 19:12:25 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	get_color(t_image *img, int x, int y)
{
	char	*dst;

	//printf("x: %i\n", x);
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

	x_pos = x;
	y_pos = y;
	while (y < y_pos + (cub->img[asset].w * 2))
	{
		x = x_pos;
		while (x < x_pos + (cub->img[asset].w * 2))
		{
			my_mlx_pixel_put(&cub->img[M_MAP], x, y, \
			get_color(&cub->img[asset], (x - x_pos) / 2, \
			(y - y_pos) / 2));
			x++;
		}
		y++;
	}
}
void	render_map(t_cub *cub)
{
	int	i;
	int	j;

	render_image_to_map(cub, MAP, 0, 0);
	render_image_to_map(cub, M_MARIO, cub->layout.mario_x, cub->layout.mario_y);
	j = -1;
	while(cub->map.map[++j])
	{
		i = -1;
		while (cub->map.map[j][++i])
		{
			render_image_to_map(cub, M_WALL, fabs((cub->player.x - i) * 16), \
			fabs((cub->player.y - j) * 16));
		}
	}
	render_image_to_map(cub, M_LAYER, 0, 0);
	render_image(cub, M_MAP, cub->layout.map_x, cub->layout.map_y);
}

void	render_frame(t_cub *cub)
{
	render_map(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img[FRAME].img, 0, 0);
	return ;
}
