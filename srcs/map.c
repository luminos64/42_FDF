/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usoontra <usoontra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:08:36 by usoontra          #+#    #+#             */
/*   Updated: 2024/12/08 21:54:11 by usoontra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_height(char *file, t_map *map, char *line, int fd)
{
	char	**x_array;
	int		x;

	fd = open(file, O_RDONLY);
	line = gnl(fd);
	if (fd < 0 || !line)
		map_error(map, NULL, NULL, 0);
	while (line)
	{
		if (map->height == 0)
		{
			x_array = split_space(line);
			if (!x_array)
				map_error(map, line, NULL, 1);
			x = 0;
			while (x_array[x])
				x++;
			free_split(x_array);
		}
		free(line);
		map->width = x;
		map->height++;
		line = gnl(fd);
	}
	close(fd);
}

static t_point	*set_x(t_point *point, char **x_array, t_map *map, int *y)
{
	int		x;
	char	**parts;

	x = 0;
	while (x_array[x] && x < map->width)
	{
		point[x].y = y[0];
		point[x].x = x;
		parts = ft_split((x_array[x]), ',');
		if (!parts)
			y[1] = -1;
		if (!isnum(parts[0], 10) || (parts[1] && !isnum(parts[1], 16)))
			y[1] = -1;
		point[x].z = ft_atoi(parts[0]);
		if (point[x].z < map->z_min)
			map->z_min = point[x].z;
		if (point[x].z > map->z_max)
			map->z_max = point[x].z;
		point[x].color = -1;
		if (parts[1])
			point[x].color = ft_atoi_base(parts[1], 16);
		x++;
		free_split(parts);
	}
	return (point);
}

static int	get_width(t_map *map, char	**x_array)
{
	int	x;

	x = 0;
	while (x_array[x])
		x++;
	if (x < 2)
		return (0);
	if (map->width != x)
		return (0);
	return (1);
}

void	get_line(t_map *map, int *y, int fd)
{
	char	*line;
	char	**x_array;

	line = gnl(fd);
	while (line)
	{
		x_array = split_space(line);
		if (!x_array)
			y[1] = -1;
		if (!get_width(map, x_array))
			y[1] = -1;
		map->pos[y[0]] = malloc((sizeof(t_point) * map->width));
		if (!map->pos[y[0]])
			y[1] = -1;
		map->pos[y[0]] = set_x(map->pos[y[0]], x_array, map, y);
		free_split(x_array);
		free(line);
		y[0]++;
		line = gnl(fd);
	}
}

int	set_array(char *file, t_map *map)
{
	int		fd;
	int		y[2];

	fd = open(file, O_RDONLY);
	if (fd < 0)
		map_error(map, NULL, NULL, 0);
	y[0] = 0;
	map->z_min = 0;
	map->z_max = 0;
	y[1] = 0;
	get_line(map, y, fd);
	if (y[1] < 0)
	{
		free_map(map->pos, map);
		ft_putstr_fd("====== MAP ERROR ======\n", 2);
		exit (1);
	}
	return (0);
}
