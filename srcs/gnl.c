/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usoontra <usoontra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:00:30 by usoontra          #+#    #+#             */
/*   Updated: 2024/12/07 18:24:23 by usoontra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*shift_lst(t_list **list, char *buffer, int len)
{
	t_list	*temp;
	char	*line;
	int		j;
	int		i;

	i = ft_lstsize(*list);
	temp = *list;
	line = malloc(sizeof(char) * ((i * BUFFER_SIZE) + len + 1));
	j = 0;
	while (temp)
	{
		i = 0;
		while (temp->content[i])
			line[j++] = temp->content[i++];
		temp = temp->next;
	}
	ft_lst_clear(list);
	i = 0;
	while (i < len)
		line[j++] = buffer[i++];
	line[j] = '\0';
	*list = ft_lst_new(buffer + i);
	return (line);
}

static int	find_next(char *buffer, int bytes, t_list **list, t_list **last)
{
	int	len;

	len = 0;
	while (buffer[len] != '\0' && len < bytes)
	{
		if (buffer[len] == '\n')
			return (len + 1);
		len++;
	}
	if (buffer[len] == '\n')
		len++;
	if (len == bytes)
	{
		ft_lst_addback(list, last, ft_lst_new(buffer));
		if (!*last)
			return (0);
		return (0);
	}
	return (len);
}

static char	*ft_reader(int fd, char *buffer, t_list **list, char *line)
{
	static int	bytes;
	t_list		*last;
	int			len;

	last = NULL;
	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		else if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		if (bytes > 0)
		{
			len = find_next(buffer, bytes, list, &last);
			if (len)
			{
				line = shift_lst(list, buffer, len);
				return (line);
			}
		}
	}
	return (line);
}

static char	*ft_left_over(t_list **list)
{
	char	*line;
	size_t	len;

	len = 0;
	while ((*list)->content[len] != '\0')
	{
		if ((*list)->content[len] == '\n')
			break ;
		len++;
	}
	if (len < ft_strlen((*list)->content))
	{
		len += 1;
		line = malloc(sizeof(char) * len + 1);
		fill_line(list, line, len);
		return (line);
	}
	else
		return (NULL);
}

char	*gnl(int fd)
{
	static t_list	*list;
	char			buffer[BUFFER_SIZE + 1];
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (list)
	{
		line = ft_left_over(&list);
		if (line)
			return (line);
	}
	line = ft_reader(fd, buffer, &list, line);
	if (!line)
		return (NULL);
	return (line);
}

// int	main(void)
// {
// 	int	fd = open("./test_maps/basictest.fdf", O_RDONLY);
// 	char	*line;
// 	int	i = 1;

// 	line = gnl(fd);
// 	while (i < 15)
// 	{
// 		printf("%2d | %s", i, line);
// 		if (!line)
// 			printf("\n");
// 		free(line);
// 		i++;
// 		line = gnl(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
