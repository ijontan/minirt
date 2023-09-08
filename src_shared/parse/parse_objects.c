/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:14:41 by rsoo              #+#    #+#             */
/*   Updated: 2023/09/09 11:34:44 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// the objects consists of a sphere, plane and cylinder
#include "minirt.h"

void    parse_sphere(t_parse *p)
{
    t_sphere	*sphere;

    sphere = ft_calloc(1, sizeof(t_sphere));

    sphere->center = parse_coordinates(p->info[1], p);

    sphere->radius = ft_atof(p->info[2], p) / 2;
    if (sphere->radius <= 0.0)
        exit_parse(p->info, "Sphere", 'd');

    if (check_rgb(p->info[3], p))
        sphere->material.color = color_correct((t_color)color_new(0, p->rgb[0],
                p->rgb[1], p->rgb[2]));
    else
        exit_parse(p->info, "Sphere", 'c');
	
    add_object(&p->objects, sphere, SPHERE);
}

void parse_plane(t_parse *p)
{
    t_plane	*plane;

    plane = ft_calloc(1, sizeof(t_plane));

	p->plane.point_on_plane = parse_coordinates(p->info[1], p);

	if (check_normalized(p->info[2], p))
		p->plane.normalized_norm_vec = assign_norm_vec(p);
	else
		exit_parse(p->info, "Plane", 'n');

	if (check_rgb(p->info[3], p))
		p->plane.material.color = color_correct(\
			(t_color)color_new(0, p->rgb[0], p->rgb[1], p->rgb[2]));
	else
		exit_parse(p->info, "Plane", 'c');

    add_object(&p->objects, plane, PLANE);
}

void parse_cylinder(t_parse *p)
{
	t_cylinder	*cylinder;

    cylinder = ft_calloc(1, sizeof(t_cylinder));
	p->cylinder.center = parse_coordinates(p->info[1], p);

	if (check_normalized(p->info[2], p))
		p->cylinder.normalized_axis = assign_norm_vec(p);
	else
		exit_parse(p->info, "Cylinder", 'n');

	p->cylinder.radius = ft_atof(p->info[3], p) / 2;
	if (p->cylinder.radius <= 0.0)
		exit_parse(p->info, "Cylinder", 'd');

	p->cylinder.height = ft_atof(p->info[4], p);
	if (p->cylinder.height <= 0.0)
		exit_parse(p->info, "Cylinder", 'h');
		
	if (check_rgb(p->info[5], p))
		p->cylinder.material.color = color_correct(\
			(t_color)color_new(0, p->rgb[0], p->rgb[1], p->rgb[2]));
	else
		exit_parse(p->info, "Cylinder", 'c');

    add_object(&p->objects, cylinder, CYLINDER);
}

