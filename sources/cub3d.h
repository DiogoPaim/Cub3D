/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:30:19 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/26 17:24:51 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx_int.h"
# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <sys/types.h> 
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>

# define ASSET_NUMBER 4

typedef enum assets
{
	N,
    S,
    W,
    E
}	t_assets;

typedef struct s_timeval
{
	time_t			tv_sec;
	suseconds_t		tv_usec;
}	t_timeval;

typedef struct s_image
{
	void	*img;
	char	*addr;
	char	*path;
	int		bpp;
	int		line_length;
	int		endian;
	int		h;
	int		w;
	int		created;
}	t_image;

typedef struct s_frame
{
	t_image		back;
	t_image		hand;
	t_image		UI;
}	t_frame;

typedef struct s_map
{
	char	**map;
	char	*pre_map;
	char	*path;
	int		collect_nb;
	int		h;
	int		w;
	int		player_y;
	int		player_x;
	char	player_dir;
}	t_map;

typedef struct s_cub
{
	void				*mlx;
	void				*window;
	t_frame				frame;
	t_map				map;
	t_image				*asset;
	t_timeval			time;
	char				*arg[6];
	int					x;
	int					y;
}	t_cub;

//MAIN
//main.c

//initializer.c
void	cub_initializer(t_cub *cub);

//free_utils.c
void	free_cub(t_cub *cub, int exit_code);
void	free_split(char **split);

//PARSER
//parser.c
void	*parser(int argc, char **argv, t_cub *cub);

#endif
