#include "../cub3d.h"

void	render_limits(t_cub *cub, int x, int c_pos, int f_pos)
{
	int	i;

	i = 0;
	while (i <= c_pos)
	{
		my_mlx_pixel_put_real(&cub->img[FRAME], x, i, cub->ceiling);
		i += 1 + (1 * PIXEL_SKIP);
	}
	i = (f_pos / (1 + PIXEL_SKIP) * (1 + PIXEL_SKIP));
	while (i < Y_RES)
	{
		my_mlx_pixel_put_real(&cub->img[FRAME], x, i, cub->floor);
		i += 1 + (1 * PIXEL_SKIP);
	}
}

void	render_lines(t_ray *ray, t_cub *cub, int ray_n)
{
	double		step;
	t_line		d_line;

	
	if (ray->perp_wall_dist > 0)
	{
		d_line.height = (int)(Y_RES / ray->perp_wall_dist);
		step = 1.0 * (cub->img[ray->dir_wall].h / d_line.height);
		d_line.start = -d_line.height / 2 + Y_RES / (2);
		d_line.end = d_line.height / 2 + Y_RES / (2);
		d_line.x_in_texture = coordinate_x_text(cub, ray, get_wallx(cub, ray));
		d_line.y_stepper = (d_line.start - Y_RES / 2 + d_line.height / 2) * step;
		d_line.x_coordinate = ray_n;
		draw_textured_line(ray, cub, &d_line, ray->dir_wall);
	}
}

void	render_door(t_ray *ray, t_cub *cub, int ray_n)
{
	double		step;
	t_line		d_line;

	
	if (ray->perp_wall_dist > 0)
	{
		d_line.height = (int)(Y_RES / ray->perp_wall_dist);
		step = 1.0 * cub->img[ray->dir_wall].h / d_line.height;
		d_line.start = -d_line.height / 2 + Y_RES / (2);
		d_line.end = d_line.height / 2 + Y_RES / (2);
		d_line.x_in_texture = coordinate_x_text(cub, ray, get_wallx(cub, ray));
		d_line.y_stepper = (d_line.start - Y_RES / 2 + d_line.height / 2) * step;
		d_line.x_coordinate = ray_n;
		draw_textured_line(ray, cub, &d_line, DOOR);
	}
}

void	draw_textured_line(t_ray *ray, t_cub *cub, t_line *d_line, \
	int asset_n)
{
	
	int				y_in_tex;
	int				i;
	int				normalized;
	int				y;
	double			step;

	render_limits(cub, d_line->x_coordinate, d_line->start, d_line->end);
	normalized = ((int) d_line->start / (1 + PIXEL_SKIP)) * (1 + PIXEL_SKIP);
	i = 0;
	step = 1.0 * cub->img[ray->dir_wall].h / d_line->height;
	while (normalized + i <= d_line->end)
	{
		y_in_tex = (int)d_line->y_stepper;
        d_line->y_stepper += step;
		if (i % (PIXEL_SKIP + 1) != 0)
		{
			i ++;
			continue;
		}
		y = normalized + i;
		my_mlx_pixel_put_real(&cub->img[FRAME], d_line->x_coordinate, y, \
		get_color(&cub->img[asset_n], d_line->x_in_texture, y_in_tex));
		i ++;
	}
}

