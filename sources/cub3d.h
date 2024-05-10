/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:30:19 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/05/09 17:23:00 by tjorge-d         ###   ########.fr       */
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

# define UI_SCALE 3
# define TRANSPARENT 16777215
# define SIZE 64
# define X_RES 1920
# define Y_RES 1080
# define SPEED 0.05
# define SENSITIVITY 50
# define M_PI 3.14159265358979323846
# define FRAME_RATE 160
# define WALL_HEIGHT 50
# define FOV 72
# define MAP_RANGE 4

# define ASSET_NUMBER 13
# define IMG_NUMBER 3
typedef enum assets
{
	N,
    S,
    W,
    E,
	FLOOR_TOP,
	WALL_TOP,
	PLAYER_TOP,
	M_BACKGROUND,
	M_LAYER,
	M_WALL,
	M_MARIO,
	M_GOOMBA,
	M_MUSHROOM,
	M_MAP,
	MAP,
	FRAME,
	COVER
}	t_assets;


typedef enum side
{
	NORTHSOUTH,
    WESTEAST
}	t_side;

typedef enum direction
{
	NORTH,
	SOUTH,
    WEST,
	EAST
}	t_direction;

typedef enum type
{
	FORE = 119,
	LEFT = 97,
	AFT = 115,
	RIGHT = 100,
	ESC = 65307
}	t_type;

typedef struct s_layout
{
	float	map_size;
	float	border_size;
	int		map_x;
	int		map_y;
	int		mario_x;
	int		mario_y;
}	t_layout;

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
	float	scale;
	int		created;
}	t_image;

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
	float			angle;
	float			height;
	float			dir_v[2];
}	t_player;

typedef struct s_map
{
	char		**map;
	char		*pre_map;
	char		*path;
	int			collect_nb;
	int			h;
	int			w;
	int			player_y;
	int			player_x;
	char		player_dir;
}	t_map;

typedef struct s_camera
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	fov_rad;
	double	x;
}	t_camera;

typedef struct s_ray
{
	int					x;
	int					y;
	double				side_d_x;
	double				side_d_y;
	double				delta_d_x;
	double				delta_d_y;
	int					step_x;
	int					step_y;
	double				dir_x;
	double				dir_y;
	int					side_hit;
	double				perp_wall_dist;
	int					dir_wall;
}	t_ray;

typedef struct s_cub
{
	void				*mlx;
	void				*window;
	long				last_frame;
	t_map				map;
	t_image				*img;
	t_layout			layout;
	struct timeval		time;
	t_player			player;
	char				**arg;
	t_ray				ray;
}	t_cub;

//MAIN
//frame_painter.c
unsigned int	get_color(t_image *img, int x, int y);
void			render_map(t_cub *cub);
void			my_mlx_pixel_put(t_image *img, int x, int y, int color);
void			render_image(t_cub *cub, int asset, int x, int y);
void			paint_map_background(t_cub *cub, int asset, int width, int height);
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
void	init_camera(t_cub *cub, t_camera *camera);
void	paint_back(t_cub *cub);

//draw_sight_line
void	draw_line_sight_based_on_angle(t_cub *cub);

//dda_basic 
double	actual_dda(t_cub *cub, t_ray *ray);
void	calc_delta_distance(t_ray *ray);
void	calculate_ray_steps(t_ray *ray, t_cub *cub);
double	calculate_dist(t_ray *ray);
void	initialize_ray(t_cub *cub, t_ray *ray, int ray_n, t_camera *camera);


//dda_combo
void	barrage_of_rays(t_cub *cub);
int get_wall_direction(t_ray *ray);

//drawer
void draw_vertical_line(t_cub *cub, int x, int line_range[2], int color);


#endif
