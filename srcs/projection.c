/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usoontra <usoontra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 03:19:15 by usoontra          #+#    #+#             */
/*   Updated: 2024/12/08 20:20:05 by usoontra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(t_fdf *data, float *y, float *z)
{
	float	prev_y;

	prev_y = *y;
	*y = (prev_y * cos(data->rotate_x)) + (*z * sin(data->rotate_x));
	*z = (-prev_y * sin(data->rotate_x)) + (*z * cos(data->rotate_x));
}

void	rotate_y(t_fdf *data, float *x, float *z)
{
	float	prev_x;

	prev_x = *x;
	*x = (prev_x * cos(data->rotate_y)) + (*z * sin(data->rotate_y));
	*z = (-prev_x * sin(data->rotate_y)) + (*z * cos(data->rotate_y));
}

void	rotate_z(t_fdf *data, float *x, float *y)
{
	float	prev_x;

	prev_x = *x;
	*x = (prev_x * cos(data->rotate_z)) - (*y * sin(data->rotate_z));
	*y = (prev_x * sin(data->rotate_z)) + (*y * cos(data->rotate_z));
}

void	isometric(t_fdf *data, float *x, float *y, float z)
{
	float	prev_x;
	float	prev_y;

	if (!data->isometric)
		return ;
	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.5235);
	*y = (prev_x + prev_y) * sin(PI / 6) - z;
}

void	view_camera(t_fdf *data, mlx_key_data_t key)
{
	if (key.key == MLX_KEY_T)
	{
		reset_win(data);
		data->shift_y = WINY / 2;
		data->isometric = 0;
	}
	if (key.key == MLX_KEY_F)
	{
		reset_win(data);
		data->rotate_x = -1.58;
		data->isometric = 0;
	}
	if (key.key == MLX_KEY_G)
	{
		reset_win(data);
		data->shift_y = WINY / 2;
		data->rotate_y = 1.58;
		data->rotate_z = -1.58;
		data->isometric = 0;
	}
}
