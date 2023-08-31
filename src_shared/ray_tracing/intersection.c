/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:46:40 by itan              #+#    #+#             */
/*   Updated: 2023/08/31 11:51:48 by rsoo             ###   ########.fr       */
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
t_hit_info	intersections(t_minirt *minirt, t_ray *ray, unsigned int *state)
{
	int			i;
	t_vec3		prev_intersect;
	t_vec3		intersect;
	t_hit_info	hit_info;
	int			hit_index;

	i = -1;
	(void)state;
	hit_index = -1;
	prev_intersect = vec3_new(0, 0, 0);
	hit_info.hit = false;

	// sphere intersect
	while (++i < 4)
	{
		intersect = sphere_intersect(minirt->sphere + i, ray);
		if (intersect.z > 0)
		{
			if (prev_intersect.z == 0 || intersect.x < prev_intersect.x)
			{
				hit_info.material = minirt->sphere[i].material;
				prev_intersect = intersect;
				hit_index = i;
				hit_info.hit = true;
			}
		}
	}

	// cylinder intersect
	intersect = cylinder_intersect(minirt->cylinder, ray);
	if (intersect.z > 0)
	{
		if (prev_intersect.z == 0 || intersect.x < prev_intersect.x)
		{
			hit_info.material = minirt->cylinder->material;
			prev_intersect = intersect;
			hit_index = -2;
			hit_info.hit = true;
		}
	}

	// plane intersect
	intersect = plane_intersect(minirt->plane, ray);
	if (intersect.z > 0)
	{
		if (prev_intersect.z == 0 || intersect.x < prev_intersect.x)
		{
			hit_info.material = minirt->plane->material;
			prev_intersect = intersect;
			hit_index = -2;
			hit_info.hit = true;
		}
	}

	if (hit_info.hit == false)
		return (hit_info);
	hit_info.point = vec3_multiply(ray->direction, prev_intersect.x);
	if (hit_index == -2)
	{
		hit_info.point = vec3_add(ray->origin, hit_info.point);
		hit_info.normal = vec3_subtract(hit_info.point,
			minirt->cylinder->center);
	}
	else
	{
		hit_info.point = vec3_add(ray->origin, hit_info.point);
		hit_info.normal = vec3_subtract(minirt->sphere[hit_index].center,
			hit_info.point);
	}
	hit_info.normal = vec3_normalize(hit_info.normal);
	return (hit_info);
}
