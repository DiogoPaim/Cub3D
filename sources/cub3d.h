/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:30:19 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/03 16:17:29 by tjorge-d         ###   ########.fr       */
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
# include <math.h>
# include <sys/time.h>
# include <sys/types.h> 
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>
# include <float.h>
# include <math.h>

# define SIZE 64
# define SPEED 0.05
# define ASSET_NUMBER 7
# define SENSITIVITY 50
# define M_PI 3.14159265358979323846
# define FRAME_RATE 60
# define WALL_HEIGHT 200

typedef enum assets
{
	N,
    S,
    W,
    E,
	FLOOR_TOP,
	WALL_TOP,
	PLAYER_TOP
}	t_assets;

typedef enum side
{
	NORTHSOUTH,
    WESTEAST
}	t_side;

typedef enum type
{
	FORE = 119,
	LEFT = 97,
	BACK = 115,
	RIGHT = 100,
	ESC = 65307
}	t_type;

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
	long		last_frame;
}	t_frame;

typedef struct s_player
{
	int				y_mov;
	int				x_mov;
	int				mov_tool[3][3];
	float			x;
	float			y;
	float			pos_v[2];	
	float			vis_angle;
	float			mov_angle;
	float			height;
	float			dir_v[2];
}	t_player;

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
	struct timeval		time;
	t_player			player;
	char				**arg;
	int					x;
	int					y;
	int					ray_side_hit;
	double 				planeX;
	double				planeY;
}	t_cub;

//MAIN
//main.c
//hooks.c
int		key_release(int keycode, t_cub *cub);
int		key_press(int keycode, t_cub *cub);

//movement.c
int		player_movement(t_cub *cub);

//initializer.c
void	cub_initializer(t_cub *cub);

//free_utils.c
void	free_cub(t_cub *cub, int exit_code);
void	free_split(char **split);

//PARSER
void	*parser(int argc, char **argv, t_cub *cub);
void	*get_map_elements(t_cub *cub, int fd);
void	*elements_validator(t_cub *cub);
void	*get_cub_map(t_cub *cub);
void	*cub_map_validator(t_cub *cub);
void	print_map(t_cub *cub);
void    load_cub(t_cub *cub);

//JUGGLE
//mlx_window
int		open_window_4k(t_cub *mlx);
int		game_close(t_cub *mlx);
void	draw_map(t_cub *cub);
void	update_player_mouse_angle(t_cub *cub);

//draw_sight_line
void	draw_line_sight_based_on_angle(t_cub *cub);

//dda_basic 
double get_distance_vector_wall(float pos_v[2], float dir_v[2], t_cub *cub,\
	int camera_x);

//dda_combo
void barrage_of_rays(t_cub *cub);

//drawer
void draw_vertical_line(t_cub *cub, int x, int y_start, int y_end);


#endif
