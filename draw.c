/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usoontra <usoontra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 04:49:48 by usoontra          #+#    #+#             */
/*   Updated: 2024/12/08 18:57:48 by usoontra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_colour(mlx_texture_t *texture, int colour, int x, int y)
{
	size_t	p;
	int		alpha;

	if (x < 0 || y < 0)
		return ;
	if (x >= (int)texture->width || y >= (int)texture->height)
		return ;
	p = (y * texture->width * 4) + (x * 4);
	alpha = 255;
	if (colour > 0xFFFFFF)
	{
		colour = 0xFFFFFF;
		alpha = 0;
	}
	if (colour == -1)
		colour = 0xFFFFFF;
	texture->pixels[p] = (colour >> 16) & 0xFF;
	texture->pixels[p + 1] = (colour >> 8) & 0xFF;
	texture->pixels[p + 2] = (colour) & 0xFF;
	texture->pixels[p + 3] = alpha;
}

static void	apply_changes(t_fdf *data, t_point *pos)
{
	pos->x = pos->x - data->map->width / 2;
	pos->y = pos->y - data->map->height / 2;
	pos->z = pos->z * data->depth;
	pos->axis[X] = pos->x;
	pos->axis[Y] = pos->y;
	pos->axis[Z] = pos->z;
	rotate_x(data, &pos->axis[Y], &pos->axis[Z]);
	rotate_y(data, &pos->axis[X], &pos->axis[Z]);
	rotate_z(data, &pos->axis[X], &pos->axis[Y]);
	isometric(data, &pos->axis[X], &pos->axis[Y], pos->z);
	pos->axis[X] = pos->axis[X] * data->zoom + data->shift_x;
	pos->axis[Y] = pos->axis[Y] * data->zoom + data->shift_y;
}

static void	draw_line(t_fdf *data, t_point start, t_point end)
{
	t_point	d;
	t_point	p;
	int		pixels;
	int		colour[2];

	apply_changes(data, &start);
	apply_changes(data, &end);
	d.axis[X] = end.axis[X] - start.axis[X];
	d.axis[Y] = end.axis[Y] - start.axis[Y];
	pixels = sqrt((d.axis[X] * d.axis[X]) + (d.axis[Y] * d.axis[Y]));
	d.axis[X] /= pixels;
	d.axis[Y] /= pixels;
	p.axis[X] = start.axis[X];
	p.axis[Y] = start.axis[Y];
	colour[0] = pixels / 2;
	colour[1] = start.color;
	while (pixels > 0)
	{
		if (pixels < colour[0])
			colour[1] = end.color;
		set_colour(data->texture, colour[1], p.axis[X], p.axis[Y]);
		p.axis[X] += d.axis[X];
		p.axis[Y] += d.axis[Y];
		pixels = pixels - 1;
	}
}

static void	fill_bg(t_fdf *data)
{
	int	y;
	int	x;
	int	bg;

	bg = 0x10101a;
	y = 0;
	while (y < WINY)
	{
		x = 0;
		while (x < WINX)
			set_colour(data->texture, bg, x++, y);
		y++;
	}
}

void	render(void *param)
{
	int		x;
	int		y;
	t_fdf	*data;

	data = (t_fdf *)param;
	fill_bg(data);
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->c_width)
		{
			if (x < data->c_width - 1)
				draw_line(data, data->map->pos[y][x], data->map->pos[y][x + 1]);
			if (y < data->map->height - 1)
				draw_line(data, data->map->pos[y][x], data->map->pos[y + 1][x]);
			x++;
		}
		y++;
	}
	data->img = mlx_texture_to_image(data->mlx, data->texture);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	data->img->instances->z = 0;
}
