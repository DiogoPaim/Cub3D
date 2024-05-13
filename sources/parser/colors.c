/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:41:51 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/13 17:08:29 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	*commas_counter(t_cub *cub, char *arg, char **split, int fd)
{
	int	i;
	int	counter;
	
	counter = 0;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == ',')
			counter++;
	}
	if (counter != 2)
		return (printf("Error\nInvalid color elements\n"), \
		close(fd), free(arg), free_split(split), free_cub(cub, 2), NULL);
	return (NULL);
}

static void	*get_color_values(t_cub *cub, char *arg, char **split, int fd)
{
	char **args;
	
	args = ft_split(arg, ',');
	free(arg);
	if (!args)
		return (printf("Error\nFunction ft_split failed\n"), \
		close(fd), free_split(split), free_cub(cub, 2), NULL);
	if (split[0][0] == 'F')
	{
		if(cub->arg[4])
			return (printf("Error\nToo many element calls\n"), close(fd), \
			free_split(args), free_split(split), free_cub(cub, 2), NULL);
		cub->arg[4] = args[0];
		cub->arg[5] = args[1];
		cub->arg[6] = args[2];
		return (free(args), NULL);
	}
	if(cub->arg[7])
		return (printf("Error\nToo many element calls\n"), close(fd), \
			free_split(args), free_split(split), free_cub(cub, 2), NULL);
	cub->arg[7] = args[0];
	cub->arg[8] = args[1];
	cub->arg[9] = args[2];
	return (free(args), NULL);
}

static void	*check_color_values(t_cub *cub, char *arg, char **split, int fd)
{
	int	i;
	
	commas_counter(cub, arg, split, fd);
	i = 0;
	while(arg[++i])
	{
		if (arg[i] == -42 && ft_isdigit(arg[i - 1]) && ft_isdigit(arg[i + 1]))
			return (printf("Error\nInvalid color separation\n"), \
			close(fd), free(arg), free_split(split), free_cub(cub, 2), NULL);
		if (arg[i] == -42 || arg[i] == '\n')
			arg[i] = ',';
	}
	i = -1;
	while(arg[++i])
	{
		if (arg[i] != ',' && !ft_isdigit(arg[i]))
			return (printf("Error\nOnly digits for the colors are allowed\n"), \
			close(fd), free(arg), free_split(split), free_cub(cub, 2), NULL);
	}
	return (get_color_values(cub, arg, split, fd), NULL);
}

void	*proccess_color(t_cub *cub, char **split, int fd, int i)
{
	char 		*arg;
	char 		*temp;
	static char forthy[2];
	
	forthy[0] = -42;
	arg = NULL;
	while (split[++i])
	{
		temp = arg;
		arg = ft_strjoin(arg, split[i]);
		if (!arg && temp)
			return (printf("Error\nThe function ft_strjoin failed\n"), \
			close(fd), free(temp), free_split(split), free_cub(cub, 2), NULL);
		if (!arg)
			return (printf("Error\nThe function ft_strjoin failed\n"), \
			close(fd), free_split(split), free_cub(cub, 2), NULL);
		free(temp);
		temp = arg;
		arg = ft_strjoin(arg, forthy);
		if (!arg)
			return (printf("Error\nThe function ft_strjoin failed\n"), \
			close(fd), free (temp), free_split(split), free_cub(cub, 2), NULL);
		free(temp);
	}
	return (check_color_values(cub, arg, split, fd), NULL);
}
