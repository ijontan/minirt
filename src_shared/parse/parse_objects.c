/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:14:41 by rsoo              #+#    #+#             */
/*   Updated: 2023/08/29 16:31:38 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// the objects consists of a sphere, plane and cylinder
#include "minirt.h"

void parse_sphere(char **info, t_parse *p)
{
	p->sphere->center = parse_coordinates(info[1]);
	p->sphere->diameter = ft_atof(info[2]);
	p->sphere->material->color = parse_color(info[3]);
	p->mand_flag[3] = 1;
}

void parse_plane(char **info, t_parse *p)
{
	p->plane->point_on_plane = parse_coordinates(info[1]);
	p->plane->normalized_norm_vec = parse_coordinates(info[2]);
	p->cylinder->material->color = parse_color(info[3]);
	p->mand_flag[4] = 1;
}

void parse_cylinder(char **info, t_parse *p)
{
	p->cylinder->center = parse_coordinates(info[1]);
	p->cylinder->normalized_axis = parse_coordinates(info[2]);
	p->cylinder->diameter = ft_atof(info[3]);
	p->cylinder->height = ft_atof(info[4]);
	p->cylinder->material->color = parse_color(info[5]);
	p->mand_flag[5] = 1;
}
