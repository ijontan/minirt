/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:14:41 by rsoo              #+#    #+#             */
/*   Updated: 2023/09/27 18:02:22 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// the objects consists of a sphere, plane and cylinder
#include "minirt.h"

static void	parse_material(char *obj_type, int i, t_material *mt, t_parse *p)
{
	if (p->info[i] && ft_strncmp(p->info[i], "\n", ft_strlen(p->info[i])))
	{
		mt->specular_i = ft_atof(p->info[i], p);
		if (mt->specular_i < 0.0 || mt->specular_i > 1.0)
			exit_parse(p->info, ft_strjoin(obj_type, "specular"), 'i');
		if (check_rgb(p->info[++i], p))
			mt->specular = color_correct((t_color)color_new(0, p->rgb[0],
					p->rgb[1], p->rgb[2]));
		else
			exit_parse(p->info, ft_strjoin(obj_type, "specular"), 'c');
		mt->reflective_i = ft_atof(p->info[++i], p);
		if (mt->reflective_i < 0.0 || mt->reflective_i > 1.0)
			exit_parse(p->info, ft_strjoin(obj_type, "reflective"), 'i');
		mt->diffuse_i = ft_atof(p->info[++i], p);
		if (mt->diffuse_i < 0.0 || mt->diffuse_i > 1.0)
			exit_parse(p->info, ft_strjoin(obj_type, "diffuse"), 'i');
		mt->emission_i = ft_atof(p->info[++i], p);
		if (mt->emission_i < 0.0 || mt->emission_i > 1.0)
			exit_parse(p->info, ft_strjoin(obj_type, "emission"), 'i');
		if (check_rgb(p->info[++i], p))
			mt->emission = color_correct((t_color)color_new(0, p->rgb[0],
					p->rgb[1], p->rgb[2]));
		else
			exit_parse(p->info, ft_strjoin(obj_type, "emission"), 'c');
		mt->shininess = ft_atof(p->info[++i], p);
		if (mt->shininess < 0.0)
			exit_parse(p->info, obj_type, 's');
	}
}

void	parse_sphere(t_parse *p)
{
	t_sphere	*sphere;

	sphere = ft_calloc(1, sizeof(t_sphere));
	ft_memset(sphere, 0, sizeof(t_sphere));
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
	add_object(&p->objects, sphere, SPHERE);
}

void	parse_plane(t_parse *p)
{
	t_plane	*plane;

	plane = ft_calloc(1, sizeof(t_plane));
	ft_memset(plane, 0, sizeof(t_plane));
	plane->point_on_plane = parse_coordinates(p->info[1], p);
	if (check_normalized(p->info[2], p))
		plane->normalized_norm_vec = assign_norm_vec(p);
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
	ft_memset(cylinder, 0, sizeof(t_cylinder));
	cylinder->center = parse_coordinates(p->info[1], p);
	if (check_normalized(p->info[2], p))
		cylinder->normalized_axis = assign_norm_vec(p);
	else
		exit_parse(p->info, "Cylinder", 'n');
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
