/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:16:35 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/02 12:16:36 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	*create_map(t_cub *cub)
{
	cub->map.map = ft_split(cub->map.pre_map, '\n');
	if (!cub->map.map)
		return (printf("Error\nThe function ft_split failed\n"), \
				free_cub(cub, 2), NULL);
	return (NULL);
}

static void *add_map_row(t_cub *cub, char *row, char **split, int fd)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin(cub->map.pre_map, row);
	if (!temp)
		return(printf("Error\nThe function ft_strjoin failed\n"), \
			close(fd), free(row), free_split(split), \
			free_cub(cub, 2), NULL);
	free(cub->map.pre_map);
	cub->map.pre_map = temp;
	return (NULL);
}

void	*get_cub_map(t_cub *cub)
{
	int		fd;
	char	*line;
	char	**split;

	fd = open(cub->map.path, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		split = ft_split(line, ' ');
		if (!split)
			return (printf("Error\nThe function ft_split failed\n"), \
				close(fd), free(line), free_cub(cub, 2), NULL);
		if (split[0] && split[0][0] != '1' && !cub->map.pre_map)
			;
		else if (split[0] && split[0][0] != '1')
			return (printf("Error\nInvalid map\n"), \
				close(fd), free(line), free_cub(cub, 2), NULL);
		else
			add_map_row(cub, line, split, fd);
		free_split(split);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), create_map(cub), NULL);
}