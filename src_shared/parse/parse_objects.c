/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:14:41 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/16 21:35:26 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// the objects consists of a sphere, plane and cylinder
#include "minirt.h"

void	parse_sphere(t_parse *p)
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
	parse_material("Sphere", 4, &sphere->material, p);
	parse_material("Sphere", 4, &sphere->material, p);
	add_object(&p->objects, sphere, SPHERE);
}

void	parse_plane(t_parse *p)
{
	t_plane	*plane;

	plane = ft_calloc(1, sizeof(t_plane));
	plane->center = parse_coordinates(p->info[1], p);
	if (check_norm_vec_range(p->info[2], p))
		plane->normal = assign_norm_vec(p);
	else
		exit_parse(p->info, "Plane", 'n');
	if (check_rgb(p->info[3], p))
		plane->material.color = color_correct((t_color)color_new(0, p->rgb[0],
					p->rgb[1], p->rgb[2]));
	else
		exit_parse(p->info, "Plane", 'c');
	parse_material("Plane", 4, &plane->material, p);
	add_object(&p->objects, plane, PLANE);
}

void	parse_cylinder(t_parse *p)
{
	t_cylinder	*cylinder;

	cylinder = ft_calloc(1, sizeof(t_cylinder));
	cylinder->center = parse_coordinates(p->info[1], p);
	if (check_norm_vec_range(p->info[2], p))
		cylinder->norm_axis = assign_norm_vec(p);
	else
		exit_parse(p->info, "Cylinder", 'n');
	cylinder->rot_axis = cylinder->norm_axis;
	cylinder->radius = ft_atof(p->info[3], p) / 2;
	if (cylinder->radius <= 0.0)
		exit_parse(p->info, "Cylinder", 'd');
	cylinder->height = ft_atof(p->info[4], p);
	if (cylinder->height <= 0.0)
		exit_parse(p->info, "Cylinder", 'h');
	if (check_rgb(p->info[5], p))
		cylinder->material.color = color_correct((t_color)color_new(0,
					p->rgb[0], p->rgb[1], p->rgb[2]));
	else
		exit_parse(p->info, "Cylinder", 'c');
	parse_material("Cylinder", 6, &cylinder->material, p);
	add_object(&p->objects, cylinder, CYLINDER);
}

void	parse_cone(t_parse *p)
{
	t_cone	*cone;

	cone = ft_calloc(1, sizeof(t_cone));
	cone->tip = parse_coordinates(p->info[1], p);
	if (check_norm_vec_range(p->info[2], p))
		cone->norm_axis = assign_norm_vec(p);
	else
		exit_parse(p->info, "Cone", 'n');
	cone->rot_axis = cone->norm_axis;
	cone->radius = ft_atof(p->info[3], p) / 2;
	if (cone->radius <= 0.0)
		exit_parse(p->info, "Cone", 'd');
	cone->height = ft_atof(p->info[4], p);
	if (cone->height <= 0.0)
		exit_parse(p->info, "Cone", 'h');
	if (check_rgb(p->info[5], p))
		cone->material.color = color_correct((t_color)color_new(0, p->rgb[0],
					p->rgb[1], p->rgb[2]));
	else
		exit_parse(p->info, "Cone", 'c');
	parse_material("Cone", 6, &cone->material, p);
	cone->angle = atan(cone->radius / cone->height);
	cone->cos = cos(cone->angle);
	cone->cos_squared = ft_power(cone->cos, 2);
	add_object(&p->objects, cone, CONE);
}
