/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usoontra <usoontra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:01:16 by usoontra          #+#    #+#             */
/*   Updated: 2024/12/04 18:17:00 by usoontra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	isnum(char *s, int ctl)
{
	size_t i;

	i = 0;
	if (ctl < 2)
		return (0);
	if (s[i] == '-' && ctl == 10)
		i++;
	if (ctl == 16)
		i = i + 2;
	ctl = ctl - 10;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9' + ctl)
			i++;
		else if (ctl > 0 && (s[i] >= 'a' && s[i] < ctl + 'a'))
			i++;
		else if (ctl > 0 && s[i] >= 'A' && s[i] < ctl + 'A')
			i++;
		else if (i == ft_strlen(s) - 1 && s[i] == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}
