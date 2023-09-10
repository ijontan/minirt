/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:46:40 by itan              #+#    #+#             */
/*   Updated: 2023/09/10 12:36:38 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief find the intersection of a ray and 10 sphere
 * this needs to be optimized and changed for different shapes
 *
 * @param minirt
 * @param ray
 * @param state
 * @return t_hit_info
 */
t_hit_info	intersections(t_minirt *minirt, t_ray *ray)
{
	t_vec3		prev_intersect;
	t_vec3		intersect;
	t_hit_info	hit_info;

	// int			i;
	// i = -1;
	prev_intersect = vec3_new(INFINITY, 0, 0);
	intersect = vec3_new(INFINITY, 0, 0);
	hit_info.hit = false;
	hit_info.material.emission_i = 0;
	hit_info.material.color = color_correct_new(0, 0, 0, 0);
	hit_info.material.emission = color_correct_new(0, 0, 0, 0);
	hit_info.material.diffuse_i = 0;
	hit_info.material.specular_i = 0;
	hit_info.material.shininess = 0;
	hit_info.material.specular = color_correct_new(0, 0, 0, 0);
	hit_info.normal = vec3_new(0, 0, 0);
	hit_info.d_specular = vec3_new(0, 0, 0);
	hit_info.pt_to_cam = vec3_new(0, 0, 0);
	hit_info.pt_to_l = vec3_new(0, 0, 0);
	hit_info.intersect_pt = vec3_new(0, 0, 0);
	hit_info.obj_type = 0;
	// sphere intersect
	intersect = sphere_intersect(&minirt->sphere, ray);
	if (intersect.z > 0)
	{
		if (prev_intersect.z == 0 || intersect.x < prev_intersect.x)
		{
			hit_info.material = minirt->sphere.material;
			prev_intersect = intersect;
			hit_info.obj_type = SPHERE;
			hit_info.hit = true;
		}
	}
	// cylinder intersect
	intersect = cylinder_intersect(&minirt->cylinder, ray);
	if (intersect.z > 0)
	{
		if (prev_intersect.z == 0 || intersect.x < prev_intersect.x)
		{
			hit_info.material = minirt->cylinder.material;
			prev_intersect = intersect;
			hit_info.obj_type = CYLINDER;
			hit_info.hit = true;
		}
	}
	// plane intersect
	intersect = plane_intersect(&minirt->plane, ray);
	if (intersect.z > 0)
	{
		if (prev_intersect.z == 0 || intersect.x < prev_intersect.x)
		{
			hit_info.material = minirt->plane.material;
			prev_intersect = intersect;
			hit_info.obj_type = PLANE;
			hit_info.hit = true;
		}
	}
	if (hit_info.hit == false)
		return (hit_info);
	hit_info.intersect_pt = vec3_multiply(ray->direction, prev_intersect.x);
	hit_info.intersect_pt = vec3_add(ray->origin, hit_info.intersect_pt);
	if (hit_info.obj_type == SPHERE)
		hit_info.normal = vec3_subtract(hit_info.intersect_pt,
										minirt->sphere.center);
	else if (hit_info.obj_type == PLANE)
		hit_info.normal = vec3_multiply(minirt->plane.normalized_norm_vec, -1);
	else if (hit_info.obj_type == CYLINDER)
		hit_info.normal = vec3_subtract(hit_info.intersect_pt,
										minirt->cylinder.center);
	hit_info.normal = vec3_normalize(hit_info.normal);
	return (hit_info);
}

typedef t_vec3	(*t_ft_intersect)(void *, t_ray *);

t_hit_info	intersect_list(t_minirt *minirt, t_ray *ray)
{
	t_vec3		prev_intersect;
	t_vec3		intersect;
	t_hit_info	hit_info;
	t_list		*lst;
	t_object	*tmp;

	const t_ft_intersect intersect_ft[3] = {
		(t_ft_intersect)&sphere_intersect,
		(t_ft_intersect)&cylinder_intersect,
		(t_ft_intersect)&plane_intersect,
	};
	lst = minirt->objects;
	prev_intersect = vec3_new(INFINITY, 0, 0);
	intersect = vec3_new(INFINITY, 0, 0);
	hit_info.hit = false;
	hit_info.material.emission_i = 0;
	hit_info.material.color = color_correct_new(0, 0, 0, 0);
	hit_info.material.emission = color_correct_new(0, 0, 0, 0);
	hit_info.material.diffuse_i = 0;
	hit_info.material.specular_i = 0;
	hit_info.material.shininess = 0;
	hit_info.material.specular = color_correct_new(0, 0, 0, 0);
	hit_info.normal = vec3_new(0, 0, 0);
	hit_info.d_specular = vec3_new(0, 0, 0);
	hit_info.pt_to_cam = vec3_new(0, 0, 0);
	hit_info.pt_to_l = vec3_new(0, 0, 0);
	hit_info.intersect_pt = vec3_new(0, 0, 0);
	hit_info.obj_type = 0;
	while (lst)
	{
		tmp = (t_object *)lst->content;
		intersect = (*intersect_ft[tmp->type])(tmp->object, ray);
		if (intersect.z > 0 && intersect.x > 0 && (prev_intersect.z == 0
				|| intersect.x < prev_intersect.x))
		{
			if (tmp->type == 0)
				hit_info.material = ((t_sphere *)tmp->object)->material;
			if (tmp->type == 1)
				hit_info.material = ((t_cylinder *)tmp->object)->material;
			if (tmp->type == 2)
				hit_info.material = ((t_plane *)tmp->object)->material;
			prev_intersect = intersect;
			hit_info.obj_type = tmp->type;
			hit_info.hit = true;
			hit_info.object = tmp;
		}
		lst = lst->next;
	}
	if (hit_info.hit == false)
		return (hit_info);
	hit_info.intersect_pt = vec3_multiply(ray->direction, prev_intersect.x);
	hit_info.intersect_pt = vec3_add(ray->origin, hit_info.intersect_pt);
	if (hit_info.obj_type == 0)
	{
		hit_info.normal = ((t_sphere *)(hit_info.object->object))->center;
		hit_info.normal = vec3_subtract(hit_info.intersect_pt, hit_info.normal);
	}
	else if (hit_info.obj_type == 2)
	{
		hit_info.normal = ((t_plane *)(hit_info.object->object))->normalized_norm_vec;
		hit_info.normal = vec3_multiply(hit_info.normal, -1);
	}
	else if (hit_info.obj_type == 1)
	{
		// this is wrong
		hit_info.normal = ((t_cylinder *)(hit_info.object->object))->center;
		hit_info.normal = vec3_subtract(hit_info.intersect_pt, hit_info.normal);
	}
	hit_info.normal = vec3_normalize(hit_info.normal);
	return (hit_info);
}

// t_hit_info	intersections(t_minirt *minirt, t_ray *ray, unsigned int *state)
// {
// 	t_vec3		prev_intersect;
// 	t_vec3		intersect;
// 	t_hit_info	hit_info;

// 	(void)state;
// 	prev_intersect = vec3_new(0, 0, 0);
// 	hit_info.hit = false;
// 	hit_info.obj_type = 0;

// 	// sphere intersect
// 	intersect = sphere_intersect(&minirt->sphere, ray);
// 	// printf("sphere intersection: %f\n", intersect.z);
// 	if (intersect.z > 0)
// 	{
// 		if (prev_intersect.z == 0 || intersect.z < prev_intersect.z)
// 		{
// 			hit_info.material = minirt->sphere.material;
// 			hit_info.obj_type = SPHERE;
// 			prev_intersect = intersect;
// 			hit_info.hit = true;
// 		}
// 	}

// 	// cylinder intersect
// 	intersect = cylinder_intersect(&minirt->cylinder, ray);
// 	if (intersect.z > 0)
// 	{
// 		if (prev_intersect.z == 0 || intersect.z < prev_intersect.z)
// 		{
// 			hit_info.material = minirt->cylinder.material;
// 			hit_info.obj_type = 2;
// 			prev_intersect = intersect;
// 			hit_info.hit = true;
// 		}
// 	}

// 	// plane intersect
// 	intersect = plane_intersect(&minirt->plane, ray);
// 	// printf("plane intersection: %f\n", intersect.z);
// 	if (intersect.z > 0)
// 	{
// 		if (prev_intersect.z == 0 || intersect.z < prev_intersect.z)
// 		{
// 			hit_info.material = minirt->plane.material;
// 			hit_info.obj_type = 3;
// 			prev_intersect = intersect;
// 			hit_info.hit = true;
// 		}
// 	}
// 	// printf("\n");
// 	hit_info.intersect_pt = prev_intersect;
// 	return (hit_info);
// }
