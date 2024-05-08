/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:20:23 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/08 15:49:43 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	free(split);
}

static void	free_args_n_assets(t_cub *cub)
{
    int i;

    i = -1;
	while (++i <= 5)
		free(cub->arg[i]);
	i = -1;
    while (++i < ASSET_NUMBER + 3)
    {
		if (cub->img[i].created)
        	mlx_destroy_image(cub->mlx, cub->img[i].img); 
	}
}

static void free_map(t_cub *cub)
{
	if (cub->map.pre_map)
		free(cub->map.pre_map);
	if (cub->map.map)
		free_split(cub->map.map);
}

void	free_cub(t_cub *cub, int exit_code)
{
	free_args_n_assets(cub);
	free_map(cub);
	if (exit_code == 2)
		exit(exit_code);
}