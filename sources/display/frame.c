/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:19:08 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/10 16:28:08 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

static void paint_back(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < Y_RES / 2)
	{
		x = -1;
		while (++x < X_RES)
			my_mlx_pixel_put(&cub->img[FRAME], x, y, 0);
	}
	y--;
	while (++y < Y_RES)
	{
		x = -1;
		while (++x < X_RES)
			my_mlx_pixel_put(&cub->img[FRAME], x, y, 16777214);
	}
}

void	build_frame(t_cub *cub)
{
	paint_back(cub);
	//barrage_of_rays(cub);
	alternate_barrage(cub);
	render_minimap(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img[FRAME].img, 0, 0);
}