/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usoontra <usoontra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 22:55:02 by usoontra          #+#    #+#             */
/*   Updated: 2024/12/08 20:25:07 by usoontra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <string.h>

# define WINX 2048
# define WINY 1024

# define X 0
# define Y 1
# define Z 2

# define PI 3.14159
# define INT_MAX 2147483647

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
	float	axis[3];
}	t_point;

typedef struct s_map
{
	int		width;
	int		height;
	int		z_min;
	int		z_max;
	t_point	**pos;
}	t_map;

typedef struct s_fdf
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*texture;
	t_map			*map;
	int				shift_x;
	int				shift_y;
	int				isometric;
	int				c_width;
	float			rotate_x;
	float			rotate_y;
	float			rotate_z;
	float			zoom;
	float			depth;
}	t_fdf;

char	*gnl(int fd);
void	ft_lst_clear(t_list **list);
t_list	*ft_lst_new(char *content);
void	ft_lst_addback(t_list **list, t_list **last, t_list *new);
void	fill_line(t_list **list, char *line, int len);

int		set_array(char *file, t_map *map);
void	get_height(char *file, t_map *map, char *line, int fd);
void	map_error(t_map *map, char *line, char **split, int ctl);
int		ft_atoi_base(char *nbr, int base);
void	free_map(t_point **point, t_map *map);

char	**split_space(char const *s);
void	free_map(t_point **point, t_map *map);
void	render(void *param);

void	hook(mlx_key_data_t key, void *param);
void	reset_win(t_fdf *data);
void	control_bar(t_fdf *data);

void	render(void *param);

void	rotate_x(t_fdf *data, float *y, float *z);
void	rotate_y(t_fdf *data, float *x, float *z);
void	rotate_z(t_fdf *data, float *x, float *y);
void	isometric(t_fdf *data, float *x, float *y, float z);
void	view_camera(t_fdf *data, mlx_key_data_t key);

#endif
