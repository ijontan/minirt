/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_float_and_triplet.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:35:17 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/17 11:35:17 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool    exit_float_err(char *s)
{
    printf("\e[0;31mError: float %s is not valid \
            \nExpected float format example: 0.4\e[0m\n\n", s);
    return (false);
}

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
		return (exit_float_err(s));
	while (ft_isdigit(s[i]))
		i++;
	if (!s[i])
		return (true);
	if (s[i] == '.')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	if (s[i])
		return (exit_float_err(s));
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
		printf("\e[0;31mInvalid triplet: %s\e[0m\n", s);
		free_2darray(val);
		return (false);
	}
	while (++i < 3)
	{
		if (!valid_float(val[i]))
		{
			printf("\e[0;31mInvalid float: %s\e[0m\n", val[i]);
			free_2darray(val);
			return (false);
		}
	}
	free_2darray(val);
	return (true);
}
