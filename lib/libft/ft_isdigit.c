/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usoontra <usoontra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:31:18 by usoontra          #+#    #+#             */
/*   Updated: 2024/10/30 17:00:49 by usoontra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_isdigit(int c, int ctl)
// {
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	ctl = ctl - 10;
// 	if (ctl > 0 && (ctl < ctl + 'a' || ctl < ctl + 'A'))
// 		return (1);
// 	return (0);
// }

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

//#include <stdio.h>
//#include <ctype.h>

// int	main(void)
// {
// 	char	a = 'D';
// 	char	b = '4';
// 	char	c = ' ';

// 	printf("a = %c, b = %c, c = %c\n", a, b, c);
// 	printf("ft a = %d, b = %d, ", ft_isdigit(a), ft_isdigit(b));
// 	printf("c = %d\n", ft_isdigit(c));
// 	printf("ct a = %d, b = %d c = %d\n", isdigit(a), isdigit(b), isdigit(c));
// }
