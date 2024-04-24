/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:30:02 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/24 11:47:37 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	map_name_validator(t_cub *cub, char *file)
{
	int	i;
	int	error;

	error = 0;
	i = ft_strlen(file);
	if (i == 0 || file[--i] != 'b')
		error = 1;
	if (i == 0 || file[--i] != 'u')
		error = 1;
	if (i == 0 || file[--i] != 'c')
		error = 1;
	if (i == 0 || file[--i] != '.')
		error = 1;
	if (i == 0 || file[--i] == '/')
		error = 1;
	if (error)
		return (printf("Error\nI demand a valid map name.\n"), \
			free (cub), exit(2), NULL);
	return (file);
}

static t_img	get_map_asset(t_cub *cub, char *asset, int fd)
{
	int		fd;
	char	*line;
	
	fd = open(cub->map.path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		printf("Error\nNo '%s' found in the map given");
		free_cub(cub);
	}
	while (line != NULL)
	{
		
		free(line);
		i++;
		row = get_next_line(fd);
	}
	free(line);
	exit (2);
}

static void	*get_map_elements(t_cub *cub)
{
	int	fd;
	
	fd = open(cub->map.path, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nI demand an existing map.\n"), \
			close(fd), exit(2), NULL);
	close(fd);
	cub->asset[N] = get_map_asset(cub, "NO", fd);
	cub->asset[S] = get_map_asset(cub, "SO", fd);
	cub->asset[W] = get_map_asset(cub, "WE", fd);
	cub->asset[E] = get_map_asset(cub, "EA", fd);
}

void	parser(int argc, char **argv, t_cub *cub)
{
	if (argc != 2)
		return (printf("Error\nI demand two argumens"), \
			free(cub), exit(2), NULL);
	cub->map.path = map_name_validator(cub, argv[1]);
	get_map_elements(cub);
	/*if (map->height == 0)
	{
		write (2, "Error\n", 6);
		ft_printf("Do you expect me to read an empty intel Snake?\n");
		exit(0);
	}
	map->collisions = malloc(sizeof(char *) * (map->height + 1));
	if (!map->collisions)
		exit(0);
	map->collisions[map->height] = NULL;
	row_creator(map, file);
	map_checker(map);
	map_transformer(map);
	return (NULL);*/
}
