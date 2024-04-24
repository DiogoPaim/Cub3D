/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:20:23 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/24 17:55:27 by tjorge-d         ###   ########.fr       */
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

static void	free_arguments_n_assets(t_cub *cub)
{
    int i;

    i = -1;
    while (++i < ASSET_NUMBER)
    {
		if (cub->asset[i].created)
		{
        	mlx_destroy_image(cub->mlx, cub->asset[i].img);
			if (i <= 4)
				free(cub->asset[i].path - 3); 
		}
		if (i <= 3 && cub->asset[i].path)
			free(cub->asset[i].path - 3);
		if (i <= 5 && cub->arg[i])
			free(cub->arg[i]);
	}
}

void	free_cub(t_cub *cub, int exit_code)
{
	free_arguments_n_assets(cub);
	free(cub->mlx);
	exit(exit_code);
}