/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:41:51 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/10 18:33:33 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*proccess_color(t_cub *cub, char **split, int fd)
{
	int			i;
	char 		*arg;
	char 		*temp;
	static char *forthy[2];
	
	forthy[0] = -42;
	arg = NULL;
	i = 0;
	while (split[++i])
	{
		temp = arg;
		arg = ft_strjoin(arg, split[i]);
		free(temp);
		temp = arg;
		arg = ft_strjoin(arg, forthy);
		free(temp);
	}
	i = -1;
	while(arg[++i])
	{
		if (arg[i] == -42 && ft_isdigit(arg[i - 1]) && ft_isdigit(arg[i - 1]))
			return (printf("Error\nFailed to allocate memory\n"), \
			close(fd), free_split(split), free_cub(cub, 2), NULL);
	}
	return (NULL);
}
