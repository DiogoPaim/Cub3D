/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:30:02 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/13 17:20:12 by tjorge-d         ###   ########.fr       */
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

void	print_map(t_cub *cub)
{
	int	i;

	i = -1;
	printf("\n========= ELEMENTS =========\n\n");
	printf("NO:	%s\n", cub->arg[0]);
	printf("SO:	%s\n", cub->arg[1]);
	printf("WE:	%s\n", cub->arg[2]);
	printf("EA:	%s\n", cub->arg[3]);
	printf("FR:	%s\n", cub->arg[4]);
	printf("FG:	%s\n", cub->arg[5]);
	printf("FB:	%s\n", cub->arg[6]);
	printf("CR:	%s\n", cub->arg[7]);
	printf("CG:	%s\n", cub->arg[8]);
	printf("CB:	%s\n", cub->arg[9]);
	printf("\n=========== MAP ============\n\n");
	while (cub->map.map[++i])
	{
		printf("%s\n", cub->map.map[i]);
	}
	printf("\nWidth: %i\nLenght: %i\n",cub->map.w, cub->map.h);
	printf("\n========== PLAYER ==========\n\n");
	printf("Player x:	%i\n", cub->map.player_x);
	printf("Player y:	%i\n", cub->map.player_y);
	printf("Player facing:	%c\n", cub->map.player_dir);
	printf("\n============================\n\n");
}

void	get_rgb(t_cub *cub)
{
	int	color;

	cub->floor = ft_atoi(cub->arg[4]);
//	if (cub->floor > 255)
	color = ft_atoi(cub->arg[5]);
//	if (color > 255)
	cub->floor = (cub->floor << 8) + color;
	color = ft_atoi(cub->arg[6]);
//	if (color > 255)
	cub->floor = (cub->floor << 8) + color;
	printf("F: %i\n", cub->floor);
	cub->ceiling = ft_atoi(cub->arg[7]);
	color = ft_atoi(cub->arg[8]);
//	if (color > 255)
	cub->ceiling = (cub->ceiling << 8) + color;
	color = ft_atoi(cub->arg[9]);
//	if (color > 255)
	cub->ceiling = (cub->ceiling << 8) + color;
	printf("C: %i\n", cub->ceiling);
}

void	*parser(int argc, char **argv, t_cub *cub)
{
	int	fd;

	fd = 0;
	if (argc != 2)
		return (printf("Error\nThere are more or less than 2 arguments\n"), \
			free_cub(cub, 2), NULL);
	cub->map.path = map_name_validator(cub, argv[1]);
	fd = open(cub->map.path, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nI demand an existing map.\n"), \
			free_cub(cub, 2), NULL);
	get_map_elements(cub, fd);
	elements_validator(cub);
	get_rgb(cub);
	get_cub_map(cub);
	cub_map_validator(cub);
	print_map(cub);
	return (NULL);
}
