/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usoontra <usoontra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:00:48 by usoontra          #+#    #+#             */
/*   Updated: 2024/12/08 20:19:05 by usoontra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_lst_clear(t_list **list)
{
	t_list	*temp;

	if (!list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = temp;
	}
}

t_list	*ft_lst_new(char *content)
{
	t_list	*new;

	if (!*content)
	{
		new = NULL;
		return (new);
	}
	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->next = NULL;
	return (new);
}

void	ft_lst_addback(t_list **list, t_list **last, t_list *new)
{
	if (!last || !new)
		return ;
	if (!*last && *list)
	{
		*last = *list;
		(*last)->next = new;
		*last = (*last)->next;
	}
	else if (!*last)
	{
		*last = new;
		*list = *last;
		return ;
	}
	else
	{
		(*last)->next = new;
		*last = (*last)->next;
	}
}

void	fill_line(t_list **list, char *line, int len)
{
	int		i;
	t_list	*temp;

	i = 0;
	while (i < len)
	{
		line[i] = (*list)->content[i];
		i++;
	}
	line[i] = '\0';
	temp = ft_lst_new((*list)->content + i);
	ft_lst_clear(list);
	*list = temp;
}
