/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:52:37 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/24 09:53:23 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


static void	collect_to_player(t_map *map, int y, int x, int *collect)
{
	if (map->collisions[y][x] == '0')
		map->collisions[y][x] = 'f';
	else if (map->collisions[y][x] == 'C')
	{
		map->collisions[y][x] = 'c';
		(*collect)++;
	}
	else if (map->collisions[y][x] == 'P')
		map->collisions[y][x] = 'p';
	else if (map->collisions[y][x] == 'E')
		map->collisions[y][x] = 'e';
	if (map->collisions[y][x + 1] == '0' 
	|| map->collisions[y][x + 1] == 'E' || map->collisions[y][x + 1] == 'C')
		collect_to_player(map, y, x + 1, collect);
	if (map->collisions[y + 1][x] == '0' 
	|| map->collisions[y + 1][x] == 'E' || map->collisions[y + 1][x] == 'C')
		collect_to_player(map, y + 1, x, collect);
	if (map->collisions[y][x - 1] == '0' 
	|| map->collisions[y][x - 1] == 'E' || map->collisions[y][x - 1] == 'C')
		collect_to_player(map, y, x - 1, collect);
	if (map->collisions[y - 1][x] == '0' 
	|| map->collisions[y - 1][x] == 'E' || map->collisions[y - 1][x] == 'C')
		collect_to_player(map, y - 1, x, collect);
}

static void	collect_to_exit(t_map *map, int y, int x, int *collect)
{
	if (map->collisions[y][x] == 'f')
		map->collisions[y][x] = '0';
	else if (map->collisions[y][x] == 'c')
	{
		map->collisions[y][x] = 'C';
		(*collect)++;
	}
	else if (map->collisions[y][x] == 'p')
		map->collisions[y][x] = 'P';
	else if (map->collisions[y][x] == 'e')
		map->collisions[y][x] = 'E';
	if (map->collisions[y][x + 1] == 'f' 
	|| map->collisions[y][x + 1] == 'p' || map->collisions[y][x + 1] == 'c')
		collect_to_exit(map, y, x + 1, collect);
	if (map->collisions[y + 1][x] == 'f' 
	|| map->collisions[y + 1][x] == 'p' || map->collisions[y + 1][x] == 'c')
		collect_to_exit(map, y + 1, x, collect);
	if (map->collisions[y][x - 1] == 'f' 
	|| map->collisions[y][x - 1] == 'p' || map->collisions[y][x - 1] == 'c')
		collect_to_exit(map, y, x - 1, collect);
	if (map->collisions[y - 1][x] == 'f' 
	|| map->collisions[y - 1][x] == 'p' || map->collisions[y - 1][x] == 'c')
		collect_to_exit(map, y - 1, x, collect);
}

static void	char_checker(t_map *map, int y, int x)
{
	int	exit;
	int	player;

	exit = 0;
	player = 0;
	while (map->collisions[++y] != NULL)
	{
		x = -1;
		while (map->collisions[y][++x] != '\n')
		{
			if (map->collisions[y][x] != '1' && map->collisions[y][x] != '0' 
			&& map->collisions[y][x] != 'C' && map->collisions[y][x] != 'E' 
			&& map->collisions[y][x] != 'P')
				delete_map(map->collisions, 'e');
			if (map->collisions[y][x] == 'C')
				map->collect++;
			if (map->collisions[y][x] == 'E')
				exit++;
			if (map->collisions[y][x] == 'P')
				player++;
		}
	}
	if (map->collect < 1 || exit != 1 || player != 1)
		delete_map(map->collisions, 'e');
}

static void	wall_checker(t_map *map, int y, int x, int max_y)
{
	while (y <= max_y)
	{
		if (map->collisions[y][0] != '1' \
		|| map->collisions[y][ft_strlen(map->collisions[y]) - 2] != '1')
			delete_map(map->collisions, 'e');
		if (y != max_y && ft_strlen(map->collisions[y]) \
		!= ft_strlen(map->collisions[y + 1]))
			delete_map(map->collisions, 'e');
		y++;
	}
	while (map->collisions[0][++x] != '\n')
	{
		if (map->collisions[0][x] != '1')
			delete_map(map->collisions, 'e');
	}
	x = -1;
	while (map->collisions[max_y][++x] != '\n')
	{
		if (map->collisions[max_y][x] != '1')
			delete_map(map->collisions, 'e');
	}
}

void	map_checker(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	map->collect = 0;
	wall_checker(map, 0, -1, (map->height - 1));
	map->width = ft_strlen(map->collisions[0]) - 1;
	char_checker(map, -1, -1);
	coord_finder(map);
	collect_to_player(map, map->player_y, map->player_x, &j);
	collect_to_exit(map, map->exit_y, map->exit_x, &i);
	if (j != map->collect || i != map->collect)
		delete_map(map->collisions, 'e');
}

static void	file_name_checker(char *file)
{
	int	i;
	int	error;

	error = 0;
	i = 0;
	i = ft_strlen(file);
	if (file[--i] != 'r')
		error = 1;
	if (file[--i] != 'e')
		error = 1;
	if (file[--i] != 'b')
		error = 1;
	if (file[--i] != '.')
		error = 1;
	if (file[--i] == '/')
		error = 1;
	if (error)
	{
		write(2, "Error\n", 6);
		ft_printf("Snake, that map has an invalid name.\n");
		exit(0);
	}
}

static int	row_counter(char *file)
{
	int		i;
	int		fd;
	char	*row;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\n", 6);
		ft_printf("Snake, that map does not exist.\n");
		exit(0);
	}
	row = get_next_line(fd);
	while (row != NULL)
	{
		free(row);
		i++;
		row = get_next_line(fd);
	}
	free(row);
	close(fd);
	return (i);
}

static void	row_creator(t_map *map, char *file)
{
	int	i;
	int	fd;

	i = -1;
	fd = open(file, O_RDONLY);
	while (++i < map->height)
	{
		map->collisions[i] = get_next_line(fd);
		if (!map->collisions[i])
			delete_map(map->collisions, 'c');
	}
	close(fd);
}

static void	map_transformer(t_map *map)
{
	int	j;

	j = -1;
	map->map = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!(map->map))
		delete_map(map->collisions, 'c');
	map->map[map->height] = NULL;
	while (++j < map->height)
	{
		map->map[j] = ft_strdup(map->collisions[j]);
		if (!(map->map[j]))
		{
			delete_map(map->collisions, '0');
			delete_map(map->map, 'c');
		}
	}
	transform(map, 0, 0);
}

void	**mapper(char *file, t_map *map)
{
	map->collect = 0;
	file_name_checker(file);
	map->height = row_counter(file);
	if (map->height == 0)
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
	return (NULL);
}