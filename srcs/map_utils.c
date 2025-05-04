/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usoontra <usoontra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:03:10 by usoontra          #+#    #+#             */
/*   Updated: 2024/12/08 20:19:51 by usoontra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_error(t_map *map, char *line, char **split, int ctl)
{
	if (ctl == 0)
		free(map);
	if (ctl == 1)
	{
		free(line);
		free(map);
	}
	if (ctl == 2)
	{
		free_split(split);
		free(line);
		free(map);
	}
	ft_putstr_fd("=== === MAP ERROR === ===\n", 2);
	exit (1);
}

static int	ft_todigit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

int	ft_atoi_base(char *nbr, int base)
{
	int				sign;
	int				i;
	unsigned long	res;

	i = 0;
	while ((nbr[i] > 8 && nbr[i] < 14) || nbr[i] == 32)
		i++;
	sign = 1;
	if (base == 10 && (nbr[i] == '-' || nbr[i] == '+'))
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	if (base == 16)
		i += 2;
	res = 0;
	while (nbr[i] != 0)
		res = res * base + (ft_todigit(nbr[i++]));
	return (res * sign);
}

void	free_map(t_point **point, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(point[i]);
		i++;
	}
	free(point);
	free(map);
}
