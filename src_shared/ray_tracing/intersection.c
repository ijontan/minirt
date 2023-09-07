/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:46:40 by itan              #+#    #+#             */
/*   Updated: 2023/09/07 20:42:36 by rsoo             ###   ########.fr       */
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
	int			i;
	t_vec3		prev_intersect;
	t_vec3		intersect;
	t_hit_info	hit_info;

	i = -1;
	prev_intersect = vec3_new(0, 0, 0);
	hit_info.hit = false;
	hit_info.material.emission_i = 0;
	hit_info.material.color = color_correct_new(0, 0, 0, 0);
	hit_info.material.emission = color_correct_new(0, 0, 0, 0);
	// sphere intersect
	intersect = sphere_intersect(&minirt->sphere, ray);
	if (intersect.z > 0)
	{
		if (prev_intersect.z == 0 || intersect.x < prev_intersect.x)
		{
			hit_info.material = minirt->sphere.material;
			prev_intersect = intersect;
			hit_info.obj_type = 1;
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
			hit_info.obj_type = 2;
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
			hit_info.obj_type = 3;
			hit_info.hit = true;
		}
	}


	if (hit_info.hit == false)
		return (hit_info);
	hit_info.intersect_pt = vec3_add(ray->origin, vec3_multiply(ray->direction, prev_intersect.x));
	if (hit_info.obj_type == 1)
		hit_info.normal = vec3_normalize(vec3_subtract(hit_info.intersect_pt, minirt->sphere.center));
	else if (hit_info.obj_type == 2)
		hit_info.normal = minirt->plane.normalized_norm_vec;
	else if (hit_info.obj_type == 3)
		hit_info.normal = vec3_normalize(vec3_subtract(hit_info.intersect_pt, minirt->cylinder.center));
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
// 			hit_info.obj_type = 1;
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
