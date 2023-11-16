/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:25:29 by itan              #+#    #+#             */
/*   Updated: 2023/11/16 18:25:29 by itan             ###   ########.fr       */
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
				\nExpected float format: 0.4\e[0m\n\n",
			s);
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
