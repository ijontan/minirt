/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_attr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 20:20:11 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/29 09:21:20 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color_c	parse_color(char *s)
{
	t_color_c	res;
	char		**rgb_values;
	char		rgb[3];

	rgb_values = ft_split(s, ',');
	rgb[0] = (char)ft_atoi(rgb_values[0]);
	rgb[1] = (char)ft_atoi(rgb_values[1]);
	rgb[2] = (char)ft_atoi(rgb_values[2]);
	res = color_correct((t_color)color_new(0, rgb[0], rgb[1], rgb[2]))
	free_2darray(rgb_values);
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
