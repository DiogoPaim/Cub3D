/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:30:02 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/24 18:00:20 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*map_name_validator(t_cub *cub, char *file)
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
		return (printf("Error\nInvalid map name\n"), \
			free_cub(cub, 2), NULL);
	return (file);
}

int	get_argument(char *argument)
{
	if (ft_strncmp(argument, "NO", 3) == 0)
		return (0);
	else if (ft_strncmp(argument, "SO", 3) == 0)
		return (1);
	else if (ft_strncmp(argument, "WE", 3) == 0)
		return (2);
	else if (ft_strncmp(argument, "EA", 3) == 0)
		return (3);
	else if (ft_strncmp(argument, "F", 3) == 0)
		return (4);
	else if (ft_strncmp(argument, "C", 3) == 0)
		return (5);
	return (-1);
}

void	*process_element_information(t_cub *cub, char **split, int fd)
{
	int	arg_nb;
	int	new_fd;

	new_fd = 0;
	if (split[1][ft_strlen(split[1])] == '\n' || split[1] == NULL)
		return (printf("Error\nEmpty element\n"), close (fd), \
			free_split(split), free_cub(cub, 2), NULL);
	if (split[2] != NULL)
		return (printf("Error\nToo much information in an element\n"), \
			close (fd), free_split(split), free_cub(cub, 2), NULL);
	arg_nb = get_argument(split[0]);
	if (cub->arg[arg_nb])
		return (printf("Error\nToo many element calls\n"), \
			close (fd), free_split(split), free_cub(cub, 2), NULL);
	cub->arg[arg_nb] = ft_strdup(split[1]);
	if (!cub->arg[arg_nb])
		return (printf("Error\nFailed to allocate memory\n"), \
			close (fd), free_split(split), free_cub(cub, 2), NULL);
	if (cub->arg[arg_nb][ft_strlen(cub->arg[arg_nb]) - 1] == '\n')		
		cub->arg[arg_nb][ft_strlen(cub->arg[arg_nb]) - 1] = '\0';
	new_fd = open(cub->arg[arg_nb], O_RDONLY);
	if (new_fd == -1)
		return (printf("Error\nThere is no image named '%s'\n", \
			cub->arg[arg_nb]), close (fd), \
			free_split(split), free_cub(cub, 2), NULL);
	return (close(new_fd), NULL);
}

int	is_element(char *line)
{
	if (ft_strncmp(line, "NO", 3) == 0 \
	|| ft_strncmp(line, "SO", 3) == 0 \
	|| ft_strncmp(line, "WE", 3) == 0 \
	|| ft_strncmp(line, "EA", 3) == 0 \
	|| ft_strncmp(line, "F", 3) == 0 \
	|| ft_strncmp(line, "C", 3) == 0)
		return (1);
	else
		return (0);
}

static void	*get_map_elements(t_cub *cub, int fd)
{
	char	*line;
	char	**split;

	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("$%s\n", line);
		split = ft_split(line, ' ');
		if (!split)
			return (printf("Error\nThe function ft_split failed\n"), \
				close(fd), free(line), free_cub(cub, 2), NULL);
		free(line);
		if (split[0][0] == '\n')
			;
		else if (is_element(split[0]))
			process_element_information(cub, split, fd);
		else if (!is_element(split[0]))
			return (printf("Error\nThere is an invalid element\n"), \
				close(fd), free_cub(cub, 2), NULL);
		free_split(split);
		if (cub->arg[0] != NULL && cub->arg[1] != NULL && cub->arg[2] != NULL \
		&& cub->arg[3] != NULL && cub->arg[4] != NULL && cub->arg[5] != NULL)
			break;
		line = get_next_line(fd);
	}
	return (NULL);
}

void	*parser(int argc, char **argv, t_cub *cub)
{
	int	fd;

	fd = 0;
	if (argc != 2)
		return (printf("Error\nThere are more or less than 2 arguments"), \
			free_cub(cub, 2), NULL);
	cub->map.path = map_name_validator(cub, argv[1]);
	fd = open(cub->map.path, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nI demand an existing map.\n"), \
			close(fd), free_cub(cub, 2), NULL);
	get_map_elements(cub, fd);
	printf("NO: %s\n", cub->arg[0]);
	printf("SO: %s\n", cub->arg[1]);
	printf("WE: %s\n", cub->arg[2]);
	printf("EA: %s\n", cub->arg[3]);
	printf("F: %s\n", cub->arg[4]);
	printf("C: %s\n", cub->arg[5]);
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
	map_transformer(map);*/
	return (NULL);
}
