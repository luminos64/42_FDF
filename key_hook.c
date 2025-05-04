/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usoontra <usoontra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:42:20 by usoontra          #+#    #+#             */
/*   Updated: 2024/12/08 19:57:54 by usoontra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	key_rotage(t_fdf *data, mlx_key_data_t key)
{
	if (key.key == MLX_KEY_W)
	{
		if (data->rotate_z < -6)
			data->rotate_z = 0;
		data->rotate_z -= 0.1;
	}
	if (key.key == MLX_KEY_E)
	{
		if (data->rotate_z > 6)
			data->rotate_z = 0;
		data->rotate_z += 0.1;
	}
	if (key.key == MLX_KEY_A)
		data->rotate_x -= 0.1;
	if (key.key == MLX_KEY_S)
		data->rotate_x += 0.1;
	if (key.key == MLX_KEY_Z)
		data->rotate_y -= 0.1;
	if (key.key == MLX_KEY_X)
		data->rotate_y += 0.1;
}

static void	key_shift(t_fdf *data, mlx_key_data_t key)
{
	if (key.key == MLX_KEY_UP)
		data->shift_y -= 1;
	if (key.key == MLX_KEY_DOWN)
		data->shift_y += 1;
	if (key.key == MLX_KEY_LEFT)
		data->shift_x -= 1;
	if (key.key == MLX_KEY_RIGHT)
		data->shift_x += 1;
}

static void	key_zoom(t_fdf *data, mlx_key_data_t key)
{
	if (key.key == MLX_KEY_O)
	{
		if (data->zoom > 2)
			data->zoom -= 1;
	}
	if (key.key == MLX_KEY_I)
	{
		if (data->zoom < 100)
			data->zoom += 1;
	}
}

void	hook(mlx_key_data_t key, void *param)
{
	t_fdf	*data;

	data = param;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
	{
		ft_putstr_fd("ESC end fdf\n", 2);
		mlx_delete_texture(data->texture);
		free_map(data->map->pos, data->map);
		mlx_terminate(data->mlx);
		exit(0);
	}
	if (key.key == MLX_KEY_R)
		reset_win(data);
	if (key.key == MLX_KEY_COMMA)
		data->depth -= 0.1;
	if (key.key == MLX_KEY_PERIOD)
		data->depth += 0.1;
	if (key.key == MLX_KEY_C && data->c_width > 2)
		data->c_width -= 1;
	if (key.key == MLX_KEY_V && data->c_width < data->map->width)
		data->c_width += 1;
	key_shift(data, key);
	key_zoom(data, key);
	key_rotage(data, key);
	view_camera(data, key);
}

void	control_bar(t_fdf *data)
{
	mlx_put_string(data->mlx, "HOW TO", 120, 38);
	mlx_put_string(data->mlx, "rotate z = w, e", 70, 60);
	mlx_put_string(data->mlx, "rotate x = a, s", 70, 82);
	mlx_put_string(data->mlx, "rotate y = z, x", 70, 104);
	mlx_put_string(data->mlx, "shift x = LEFT, RIGHT", 40, 140);
	mlx_put_string(data->mlx, "shift y = UP, DOWN", 55, 162);
	mlx_put_string(data->mlx, "adjust depth = <, >", 45, 200);
	mlx_put_string(data->mlx, "conic x = c, v", 75, 222);
	mlx_put_string(data->mlx, "zoom = i, o", 90, 244);
	mlx_put_string(data->mlx, "CAMERA VIEW", 90, 280);
	mlx_put_string(data->mlx, "r = reset", 95, 302);
	mlx_put_string(data->mlx, "t = top", 100, 324);
	mlx_put_string(data->mlx, "f = front", 95, 346);
	mlx_put_string(data->mlx, "g = side", 100, 368);
	mlx_put_string(data->mlx, "esc = quit", 90, 420);
}
