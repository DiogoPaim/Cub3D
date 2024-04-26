/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:30:02 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/26 15:07:19 by tjorge-d         ###   ########.fr       */
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

	if (split[1][ft_strlen(split[1])] == '\n' || split[1] == NULL)
		return (printf("Error\nEmpty element\n"), close (fd), \
			free_split(split), free_cub(cub, 2), NULL);
	if (split[2] != NULL && split[2][0] != '\n')
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
	return (NULL);
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
		split = ft_split(line, ' ');
		if (!split)
			return (printf("Error\nThe function ft_split failed\n"), \
				close(fd), free(line), free_cub(cub, 2), NULL);
		free(line);
		if (split[0][0] == '1')
			return (free_split(split), close(fd), NULL);
		if (split[0][0] == '\n')
			;
		else if (is_element(split[0]))
			process_element_information(cub, split, fd);
		else if (!is_element(split[0]))
			return (printf("Error\nThere is an invalid element\n"), \
				close(fd), free_cub(cub, 2), NULL);
		free_split(split);
		line = get_next_line(fd);
	}
	return (close(fd), NULL);
}

static void	elements_validator(t_cub *cub)
{
	int	i;
	int	fd;

	i = -1;
	fd = 0;
	while (++i <= 5)
	{
		if (cub->arg[i] == NULL)
		{
			printf("Error\nThere is elements missing\n");
			free_cub(cub, 2);
		}
		if (i <= 3)
		{
			fd = open(cub->arg[i], O_RDONLY);
			if (fd == -1)
			{
				printf("Error\nThere is no texture in the path given.\n"), \
				free_cub(cub, 2);
			}
			close(fd);
		}
	}
}

void	*create_map(t_cub *cub)
{
	cub->map.map = ft_split(cub->map.pre_map, '\n');
	if (!cub->map.map)
		return (printf("Error\nThe function ft_split failed\n"), \
				free_cub(cub, 2), NULL);
	return (NULL);
}

void *add_map_row(t_cub *cub, char *row, char **split, int fd)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin(cub->map.pre_map, row);
	if (!temp)
		return(printf("Error\nThe function ft_strjoin failed"), \
			close(fd), free(row), free_split(split), \
			free_cub(cub, 2), NULL);
	free(cub->map.pre_map);
	cub->map.pre_map = temp;
	return (NULL);
}

void	*get_cub_map(t_cub *cub, int fd)
{
	char	*line;
	char	**split;

	line = get_next_line(fd);
	while (line != NULL)
	{
		split = ft_split(line, ' ');
		if (!split)
			return (printf("Error\nThe function ft_split failed\n"), \
				close(fd), free(line), free_cub(cub, 2), NULL);
		if (split[0] && split[0][0] != '1' && split[0][0])
			;
		else if (split[0] && split[0][0] != '1' && cub->map.pre_map)
			return (printf("Error\nInvalid map\n"), \
				close(fd), free(line), free_cub(cub, 2), NULL);
		else
			add_map_row(cub, line, split, fd);
		free_split(split);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	create_map(cub);
	return (NULL);
}

static void	print_map(t_cub *cub)
{
	int	i;

	i = -1;
	while (cub->map.map[++i])
	{
		printf("%s\n", cub->map.map[i]);
	}
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
			free_cub(cub, 2), NULL);
	get_map_elements(cub, fd);
	elements_validator(cub);
	printf("NO: %s\n", cub->arg[0]);
	printf("SO: %s\n", cub->arg[1]);
	printf("WE: %s\n", cub->arg[2]);
	printf("EA: %s\n", cub->arg[3]);
	printf("F: %s\n", cub->arg[4]);
	printf("C: %s\n", cub->arg[5]);
	fd = open(cub->map.path, O_RDONLY);
	get_cub_map(cub, fd);
	print_map(cub);
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
