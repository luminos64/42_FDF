/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usoontra <usoontra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:45:11 by usoontra          #+#    #+#             */
/*   Updated: 2024/12/08 20:38:17 by usoontra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_file(char *file, t_map *map)
{
	char	*line;

	line = NULL;
	map->height = 0;
	map->width = 0;
	get_height(file, map, line, 0);
	map->pos = malloc(sizeof(t_point *) * (map->height));
	if (!map)
		map_error(map, NULL, NULL, 0);
	if (set_array(file, map))
		return ;
}

void	reset_win(t_fdf *data)
{
	int	x;
	int	y;
	int	z;

	z = data->map->z_max - data->map->z_min;
	x = WINX / (data->map->width + z) / 2;
	y = WINY / (data->map->height + z) / 2;
	if (x > y)
		data->zoom = x;
	else
		data->zoom = y;
	data->c_width = data->map->width;
	data->shift_x = WINX / 2;
	data->shift_y = WINY / 2;
	data->rotate_x = 0;
	data->rotate_y = 0;
	data->rotate_z = 0;
	data->isometric = 1;
	data->depth = 1;
}

void	set_win(t_fdf *data)
{
	reset_win(data);
	data->img = 0;
	data->texture = malloc(sizeof(mlx_texture_t));
	data->texture->height = WINY;
	data->texture->width = WINX;
	data->texture->bytes_per_pixel = 4;
	data->texture->pixels = malloc(WINX * WINY * 4 * sizeof(uint8_t));
}

void	input_screen(int argc, char **argv)
{
	int	error;
	int	len;

	error = 0;
	if (argc < 2)
		error = 1;
	len = ft_strlen(argv[1]);
	if (ft_strncmp((argv[1] + len - 4), ".fdf", 4) != 0)
		error = 1;
	if (error > 0)
	{
		ft_putstr_fd("Usage: ./fdf map.fdf\n", 2);
		exit (1);
	}
}

int	main(int argc, char **argv)
{
	t_fdf	data;

	input_screen(argc, argv);
	data.map = malloc(sizeof(t_map));
	read_file(argv[1], data.map);
	data.mlx = mlx_init(WINX, WINY, "FDF", false);
	if (!data.mlx)
		return (0);
	set_win(&data);
	mlx_key_hook(data.mlx, &hook, &data);
	mlx_loop_hook(data.mlx, &render, &data);
	control_bar(&data);
	mlx_loop(data.mlx);
	free_map(data.map->pos, data.map);
	mlx_delete_texture(data.texture);
	mlx_terminate(data.mlx);
}
