/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:17:02 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/10 17:44:52 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_element(char *argument)
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

static void *process_element_information(t_cub *cub, char **split, int fd)
{
	int	arg_nb;

	if (split[1][0] == '\n' || split[1] == NULL)
		return (printf("Error\nEmpty element\n"), close (fd), \
			free_split(split), free_cub(cub, 2), NULL);
	if (get_element(split[0]) >= 4)	
		return (proccess_color(cub, split, fd), NULL);
	if (split[2] != NULL && split[2][0] != '\n')
		return (printf("Error\nToo much information in an element\n"), \
			close(fd), free_split(split), free_cub(cub, 2), NULL);
	arg_nb = get_element(split[0]);
	if (cub->arg[arg_nb])
		return (printf("Error\nToo many element calls\n"), \
			close(fd), free_split(split), free_cub(cub, 2), NULL);
	cub->arg[arg_nb] = ft_strdup(split[1]);
	if (!cub->arg[arg_nb])
		return (printf("Error\nFailed to allocate memory\n"), \
			close(fd), free_split(split), free_cub(cub, 2), NULL);
	if (cub->arg[arg_nb][ft_strlen(cub->arg[arg_nb]) - 1] == '\n')	
		cub->arg[arg_nb][ft_strlen(cub->arg[arg_nb]) - 1] = '\0';
	return (NULL);
}

static void *check_for_valid_color(t_cub *cub, int i)
{
	char	**split;

	split = ft_split(cub->arg[i], ',');
	if (!split)
		return (printf("Error\nThe function ft_split failed\n"), \
			free_cub(cub, 2), NULL);
	if (!split[0] || !split[1] || !split[2])
		return (printf("Error\nToo few color values\n"), \
			free_split(split), free_cub(cub, 2), NULL);
	if (split[3] != NULL)
		return (printf("Error\nToo many color values\n"), \
			free_split(split), free_cub(cub, 2), NULL);
	i = -1;
	while (++i < 3)
	{
		if (ft_atoi(split[i]) > 255)
			return (printf("Error\nInvalid color value\n"), \
				free_split(split), free_cub(cub, 2), NULL);
	}
	return (free_split(split), NULL);
}

void	*get_map_elements(t_cub *cub, int fd)
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
		else if (get_element(split[0]) >= 0)
			process_element_information(cub, split, fd);
		else 
			return (printf("Error\nThere is an invalid element\n"), \
				close(fd), free_split(split), free_cub(cub, 2), NULL);
		free_split(split);
		line = get_next_line(fd);
	}
	return (close(fd), NULL);
}

void	*elements_validator(t_cub *cub)
{
	int	i;
	int	fd;

	i = -1;
	fd = 0;
	while (++i <= 5)
	{
		if (cub->arg[i] == NULL)
			return (printf("Error\nThere is elements missing\n"), \
				free_cub(cub, 2), NULL);
		if (i <= 3)
		{
			fd = open(cub->arg[i], O_RDONLY);
			if (fd == -1)
				return (printf("Error\nNo texture in the path given.\n"), \
					free_cub(cub, 2), NULL);
			cub->img[i].path = cub->arg[i];
			close(fd);
		}
		else
			check_for_valid_color(cub, i);
	}
	return (NULL);
}
