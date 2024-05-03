# include "../cub3d.h"

void draw_horizontal_line(t_cub *cub, float x2, float y2)
{
	int i;
	int x;
	int y;

	i = 0;
	if (cub->player.x*64 >= x2)
	{
		while ((cub->player.x*64) - i >= x2)
		{
			x = (int) (cub->player.x*64) - i;
			y = y2 * 64;
			mlx_pixel_put(cub->mlx,cub->window,x, y, 0xFF0000);
			i++;
		}
	}
	else
	{
		while (cub->player.x*64 + i < x2)
		{
			x = (int) (cub->player.x*64) + i;
			y = y2 * 64;
			mlx_pixel_put(cub->mlx,cub->window,x, y, 0xFF0000);
			i++;
		}
	}
}

void draw_vertical_line(t_cub *cub, float x2, float y2)
{
	int i;
	int x;
	int y;

	i = 0;
	if (cub->player.y*64 >= y2)
	{
		while ((cub->player.y*64) - i >= y2)
		{
			y = (int) (cub->player.y*64) - i;
			x = x2 * 64;
			mlx_pixel_put(cub->mlx, cub->window, x, y, 0xFF0000);
			i++;
		}
	}
	else
	{
		while (cub->player.y*64 + i < y2)
		{
			y = (int) (cub->player.y * 64) + i;
			x = x2 * 64;
			mlx_pixel_put(cub->mlx, cub->window, x, y, 0xFF0000);
			i++;
		}
	}
}
void draw_all_positive_vector(t_cub *cub, int pix_x2, int pix_y2, float angle)
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
	}
}
void draw_all_negative_vector(t_cub *cub, int pix_x2, int pix_y2, float angle)
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
	}
}
void draw_negative_positive_vector(t_cub *cub, int pix_x2, int pix_y2, float angle)
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
	}
}
void draw_positive_negative_vector(t_cub *cub, int pix_x2, int pix_y2, float angle)
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
		mlx_pixel_put(cub->mlx, cub->window, pix_x_draw, pix_y_draw, 0XFF0000);
	}
}

void	draw_vector_until(t_cub *cub,int pix_x2,int pix_y2, float angle)
{
	if(pix_x2 > cub->player.x * SIZE && pix_y2 > cub->player.y * SIZE)
		draw_all_positive_vector(cub, pix_x2, pix_y2, angle);
	else if(pix_x2 < cub->player.x * SIZE && pix_y2 < cub->player.y * SIZE)
		draw_all_negative_vector(cub, pix_x2, pix_y2, angle);
	else if(pix_x2 < cub->player.x * SIZE && pix_y2 > cub->player.y * SIZE)
		draw_negative_positive_vector(cub, pix_x2, pix_y2, angle);
	else 
		draw_positive_negative_vector(cub, pix_x2, pix_y2, angle);
}

void	draw_line_sight_based_on_angle(t_cub *cub)
{
	float	angle_rad;
	int		pix_x2;
	int		pix_y2;

	angle_rad = (M_PI * cub->player.vis_angle)/180;
	pix_x2 = (cub->player.x * SIZE) + (200 * cos(angle_rad));
	pix_y2 = (cub->player.y * SIZE) + (200 * sin(angle_rad));
	draw_vector_until(cub, pix_x2, pix_y2, angle_rad);
}