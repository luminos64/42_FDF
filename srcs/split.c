/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usoontra <usoontra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:41:08 by usoontra          #+#    #+#             */
/*   Updated: 2024/12/08 20:20:22 by usoontra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count(char const *s)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	if (*s == 0)
		return (0);
	while (s[i])
	{
		while ((s[i] >= 33 && s[i] <= 126))
			i++;
		if ((s[i] == 9 || s[i] == 32 || s[i] == '\0' || s[i] == 10) && i != 0)
			words++;
		while (s[i] && (s[i] == 9 || s[i] == 32 || s[i] == 10))
			i++;
	}
	return (words);
}

static int	ft_len(const char *s, int i)
{
	int	j;

	j = i;
	while ((s[j] >= 33 && s[j] <= 126))
		j++;
	j = j - i;
	return (j);
}

static char	**ft_free(char **str, int i)
{
	while (i >= 0)
		free(str[i--]);
	free(str);
	return (NULL);
}

static char	*sub_split(char const *s, int i)
{
	char	*res;
	int		len;
	int		j;

	len = ft_len(s, i);
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (j < len)
	{
		res[j] = s[i + j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	**split_space(char const *s)
{
	char	**res;
	int		i;
	int		j;

	res = malloc(sizeof(char *) * (count(s) + 1));
	if (!s || !res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == 9 || s[i] == 32 || s[i] == 10)
			i++;
		res[j] = sub_split(s, i);
		if (!res[j])
			return (ft_free(res, j), NULL);
		i = i + ft_len(s, i);
		while (s[i] == 9 || s[i] == 32 || s[i] == 10)
			i++;
		j++;
	}
	res[j] = NULL;
	return (res);
}

// int	main(int argc, char **argv)
// {
// 	int	fd;
// 	// char	*s = "0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n";
// 	char	**r;
// 	char	*line;
// 	int	i;

// 	(void)argc;
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (0);
// 	line = gnl(fd);
// 	// printf("%s\n", s);
// 	r = split_space(line);
// 	// r = split_space(s);
// 	// fd = open("basictest.fdf", O_RDONLY);
// 	i = 0;
// 	while (r[i])
// 	{
// 		printf("%d | %s\n", i, r[i]);
// 		free(r[i]);
// 		i++;
// 	}
// 	free(r);
// 	free(line);
// }
