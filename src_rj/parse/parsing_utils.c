/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:47:53 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/29 09:21:45 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_2darray(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		free(s[i++]);
	free(s);
}

bool	is_wspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (true);
	return (false);
}

float	atof(char *s)
{
	float	result;
	float 	power;
	int		sign;
	int		i;

	result = 0.0;
	power = 1.0;
	sign = 1;
	i = 0;
	while (is_wspace(s[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (ft_isdigit(s[i]))
		{
			result = result * 10.0 + (str[i] - '0');
			power *= 10;
			i++;
		}
	}
	return (sign * result / power);
}
