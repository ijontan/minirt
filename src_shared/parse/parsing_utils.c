/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:47:53 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/16 20:29:17 by rsoo             ###   ########.fr       */
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

static void	init_atof(t_parse *p)
{
	p->atof.result = 0.0;
	p->atof.power = 1.0;
	p->atof.sign = 1;
	p->atof.i = 0;
}

float	ft_atof(char *s, t_parse *p)
{
	init_atof(p);
	while (is_wspace(s[p->atof.i]))
		p->atof.i++;
	if (s[p->atof.i] == '-' || s[p->atof.i] == '+')
	{
		if (s[p->atof.i] == '-')
			p->atof.sign = -1;
		p->atof.i++;
	}
	while (ft_isdigit(s[p->atof.i]))
	{
		p->atof.result = p->atof.result * 10.0 + (s[p->atof.i] - '0');
		p->atof.i++;
	}
	if (s[p->atof.i] == '.')
	{
		p->atof.i++;
		while (ft_isdigit(s[p->atof.i]))
		{
			p->atof.result = p->atof.result * 10.0 + (s[p->atof.i] - '0');
			p->atof.power *= 10;
			p->atof.i++;
		}
	}
	return (p->atof.sign * p->atof.result / p->atof.power);
}
