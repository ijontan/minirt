/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:39:47 by rsoo              #+#    #+#             */
/*   Updated: 2023/11/02 11:06:16 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	plane_new(t_vec3 point, t_vec3 dir, t_material material)
{
	t_plane	plane;

	plane.point_on_plane = point;
	plane.normalized_norm_vec = dir;
	plane.material = material;
	return (plane);
}

// p: the intersection point of the ray and the plane
// p0: the centre of the disk
t_vec3	disk_intersect(t_plane *plane, t_ray *ray, float radius, t_vec3 p0)
{
	t_vec3	sols;
	t_vec3	p;
	float	len;

	sols = plane_intersect(plane, ray);
	if (!sols.x && !sols.y && !sols.z)
		return (vec3_new(0, 0, 0));
	p = vec3_add(ray->origin, vec3_multiply(ray->direction, sols.x));
	len = vec3_length(vec3_subtract(p, p0));
	if (len > radius)
		return (vec3_new(0, 0, 0));
	return (vec3_new(sols.x, 0, 2));
}

/**
 * @brief find the intersection of a ray and a plane
 *
 * @param plane
 * @param ray
 * @return t_vec3, x is theintersection,
	z is a bool to indicate if there is an intersection
 */
t_vec3	plane_intersect(t_plane *plane, t_ray *ray)
{
	float	denom;
	t_vec3	p0_l0;
	float	t;

	denom = vec3_dot(plane->normalized_norm_vec,
			vec3_normalize(ray->direction));
	if (denom > 1e-4)
	{
		p0_l0 = vec3_subtract(plane->point_on_plane, ray->origin);
		t = vec3_dot(p0_l0, plane->normalized_norm_vec) / denom;
		return (vec3_new(t, 0, 2));
	}
	return (vec3_new(0, 0, 0));
}
