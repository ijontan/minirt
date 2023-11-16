/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:23:36 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/16 20:23:36 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// checks if the float / int format is correct:
// 255: returns true
// 4.0: returns true
// 00.3
// 003
bool	valid_float(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	if ((s[i] == '0' && ft_isdigit(s[i + 1])) || s[i] == '.'
		|| !ft_isdigit(s[i]))
	{
		printf("\e[0;31mError: %s not allowed \
				\nExpected float format: 0.4\e[0m\n\n", s);
		return (false);
	}
	while (ft_isdigit(s[i]))
		i++;
	if (!s[i] || s[i] == '\n')
		return (true);
	if (s[i] == '.')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	if (s[i])
		return (false);
	return (true);
}

static bool	check_triplet_size(char **val)
{
	int	i;

	i = 0;
	while (val[i])
		i++;
	if (i == 3)
		return (true);
	return (false);
}

// checks if the triplet format (x, y, z) is correct:
bool	valid_triplet(char *s)
{
	char	**val;
	int		i;

	val = ft_split(s, ',');
	i = -1;
	if (!check_triplet_size(val))
	{
		free_2darray(val);
		return (false);
	}
	while (++i < 3)
	{
		if (!valid_float(val[i]))
		{
			free_2darray(val);
			return (false);
		}
	}
	free_2darray(val);
	return (true);
}

void	exit_parse2(char *s, char c)
{
	if (c == 'n')
	{
		if (!ft_strncmp(s, "Camera", ft_strlen(s)))
			printf("normalized orientation vector ");
		else if (!ft_strncmp(s, "Plane", ft_strlen(s)))
			printf("normalized normal vector ");
		else if (!ft_strncmp(s, "Cylinder", ft_strlen(s)))
			printf("normalized vector of axis of cylinder");
		else if (!ft_strncmp(s, "Cone", ft_strlen(s)))
			printf("normalized vector of axis of cone ");
		printf("out of range [-1, 1]\e[0m\n");
	}
}

void	exit_parse(char **info, char *s, char c)
{
	if (info)
		free_2darray(info);
	printf("\e[0;31mError: %s ", s);
	if (c == 'r')
		printf("ratio out of range [0.0, 1.0]\e[0m\n");
	else if (c == 'i')
		printf("index out of range [0.0, 1.0]\e[0m\n");
	else if (c == 'c')
		printf("color out of range [0, 255]\e[0m\n");
	else if (c == 'd')
		printf("diameter out of range [> 0.0]\e[0m\n");
	else if (c == 'h')
		printf("height out of range [> 0.0]\e[0m\n");
	else if (c == 's')
		printf("shininess out of range [> 0.0]\e[0m\n");
	else if (c == 'a')
		printf("field of view out of range [0.0, 180.0]\e[0m\n");
	exit_parse2(s, c);
	exit(EXIT_FAILURE);
}
