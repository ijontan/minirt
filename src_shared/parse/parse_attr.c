/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_attr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 20:20:11 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/29 21:10:47 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_rgb(char *s, t_parse *p)
{
	char	**rgb_values;
	int		i;

	i = -1;
	rgb_values = ft_split(s, ',');
	p->rgb[0] = ft_atoi(rgb_values[0]);
	p->rgb[1] = ft_atoi(rgb_values[1]);
	p->rgb[2] = ft_atoi(rgb_values[2]);
	while (++i < 3)
	{
		if (p->rgb[i] < 0 || p->rgb[i] > 255)
		{
			free_2darray(rgb_values);
			return (false);
		}	
	}
	free_2darray(rgb_values);
	return (true);
}

bool	check_normalized(char *s, t_parse *p)
{
	char	**comp;
	int		i;

	i = -1;
	comp = ft_split(s, ',');
	p->coords[0] = ft_atof(comp[0]);
	p->coords[1] = ft_atof(comp[1]);
	p->coords[2] = ft_atof(comp[2]);
	while (++i < 3)
	{
		if (p->coords[i] < -1.0 || p->coords[i] > 1.0)
		{
			free_2darray(comp);
			return (false);
		}	
	}
	free_2darray(comp);
	return (true);
}

t_vec3	assign_norm_vec(t_parse *p)
{
	t_vec3	res;
	
	res.x = p->coords[0];
	res.y = p->coords[1];
	res.z = p->coords[2];
	return (res);
}

t_vec3	parse_coordinates(char *s)
{
	t_vec3	res;
	char	**coords;

	coords = ft_split(s, ',');
	res.x = ft_atof(coords[0]);
	res.y = ft_atof(coords[1]);
	res.z = ft_atof(coords[2]);
	free_2darray(coords);
	return (res);
}
