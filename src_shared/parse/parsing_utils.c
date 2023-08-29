/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:47:53 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/29 22:44:42 by rsoo             ###   ########.fr       */
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

static bool	is_wspace(char c)
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
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		result = result * 10.0 + (s[i] - '0');
		i++;
	}
	if (s[i] == '.')
	{
		i++;
		while (ft_isdigit(s[i]))
		{
			result = result * 10.0 + (s[i] - '0');
			power *= 10;
			i++;
		}
	}
	return (sign * result / power);
}

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	printf("result: %f\n", atof(av[1]));
// }
