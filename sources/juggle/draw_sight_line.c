# include "../cub3d.h"

void draw_all_positive_vector(t_cub *cub, int pix_x2, int pix_y2, double angle)
{
	float i;
	float j;
	int pix_x_draw;
	int pix_y_draw;

	i = 0.0;
	j= 0.0;
	while(cub->player.x * SIZE + i <= pix_x2 && cub->player.y * SIZE + j <= pix_y2)
	{
		i += cos(angle);
		j += sin(angle);
		pix_x_draw = (int) (cub->player.x * SIZE + i);
		pix_y_draw = (int) (cub->player.y * SIZE + j);
		mlx_pixel_put(cub->mlx, cub->window, pix_x_draw, pix_y_draw, 0XFF0000);
		if(pix_x_draw > (cub->map.w * SIZE) || pix_y_draw > (cub->map.h * SIZE) \
			|| pix_x_draw < 0 || pix_y_draw < 0)
			break;
	}
}
void draw_all_negative_vector(t_cub *cub, int pix_x2, int pix_y2, double angle)
{
	float i;
	float j;
	int pix_x_draw;
	int pix_y_draw;

	i = 0.0;
	j= 0.0;
	while(cub->player.x * SIZE + i >= pix_x2 && cub->player.y * SIZE + j >= pix_y2)
	{
		i += cos(angle);
		j += sin(angle);
		pix_x_draw = (int) (cub->player.x * SIZE + i);
		pix_y_draw = (int) (cub->player.y * SIZE + j);
		mlx_pixel_put(cub->mlx, cub->window, pix_x_draw, pix_y_draw, 0XFF0000);
		if(pix_x_draw > (cub->map.w * SIZE) || pix_y_draw > (cub->map.h * SIZE) \
			|| pix_x_draw < 0 || pix_y_draw < 0)
			break;
	}
}
void draw_negative_positive_vector(t_cub *cub, int pix_x2, int pix_y2, double angle)
{
	float i;
	float j;
	int pix_x_draw;
	int pix_y_draw;

	i = 0.0;
	j= 0.0;
	while(cub->player.x * SIZE + i >= pix_x2 && cub->player.y * SIZE + j <= pix_y2)
	{
		i += cos(angle);
		j += sin(angle);
		pix_x_draw = (int) (cub->player.x * SIZE + i);
		pix_y_draw = (int) (cub->player.y * SIZE + j);
		mlx_pixel_put(cub->mlx, cub->window, pix_x_draw, pix_y_draw, 0XFF0000);
		if(pix_x_draw > (cub->map.w * SIZE) || pix_y_draw > (cub->map.h * SIZE) \
			|| pix_x_draw < 0 || pix_y_draw < 0)
			break;
	}
}
void draw_positive_negative_vector(t_cub *cub, int pix_x2, int pix_y2, double angle)
{
	float i;
	float j;
	int pix_x_draw;
	int pix_y_draw;

	i = 0.0;
	j= 0.0;
	pix_x_draw = (int) (cub->player.x * SIZE + i);
	while(cub->player.x * SIZE + i <= pix_x2 && cub->player.y * SIZE + j >= pix_y2)
	{
		pix_x_draw = (int) (cub->player.x * SIZE + i);
		pix_y_draw = (int) (cub->player.y * SIZE + j);
		i += cos(angle);
		j += sin(angle);
		if(pix_x_draw > (cub->map.w * SIZE) || pix_y_draw > (cub->map.h * SIZE) \
			|| pix_x_draw < 0 || pix_y_draw < 0)
			break;
		mlx_pixel_put(cub->mlx, cub->window, pix_x_draw, pix_y_draw, 0XFF0000);
	}
}

void	draw_vector_until(t_cub *cub,int pix_x2,int pix_y2, double angle)
{
	if(pix_x2 >= cub->player.x * SIZE && pix_y2 >= cub->player.y * SIZE)
		draw_all_positive_vector(cub, pix_x2, pix_y2, angle);
	else if(pix_x2 <= cub->player.x * SIZE && pix_y2 <= cub->player.y * SIZE)
		draw_all_negative_vector(cub, pix_x2, pix_y2, angle);
	else if(pix_x2 <= cub->player.x * SIZE && pix_y2 >= cub->player.y * SIZE)
		draw_negative_positive_vector(cub, pix_x2, pix_y2, angle);
	else 
		draw_positive_negative_vector(cub, pix_x2, pix_y2, angle);
}

void	draw_line_sight_based_on_angle(t_cub *cub)
{
	double	angle_rad;
	int		pix_x2;
	int		pix_y2;
	
	angle_rad = (M_PI * cub->player.vis_angle)/180;
	
	cub->player.dir_v[0] = cos(angle_rad);
	cub->player.dir_v[1] = sin(angle_rad);
	pix_x2 = (cub->player.x * SIZE) + (300 * cos(angle_rad));
	pix_y2 = (cub->player.y * SIZE) + (300 * sin(angle_rad));
	//draw_vector_until(cub, pix_x2, pix_y2, angle_rad);
}